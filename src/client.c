/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#include "client.h"
#include "command.h"
#include "ftp.h"
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>

static void launch_cmd(char *cmd, client_t *client)
{
    char *command = strtok(cmd, " " CLRF);

    for (size_t i = 0; i < LEN(CMD_CONST); i++) {
        if (command
            && strncmp(command, CMD_CONST[i].cmd, strlen(CMD_CONST[i].cmd))
                == 0) {
            (CMD_CONST[i].need_authentication
                && client->connexion_state != CONNECTED)
                ? reply(client->socket.fd, 530, "Need authentication")
                : CMD_CONST[i].cmd_ptr(client, strtok(NULL, CLRF));

            return;
        }
    }
    reply(client->socket.fd, 500, "Unknown command.");
}

UNUSED static void write_fd(UNUSED client_t *client)
{
}

static void read_fd(client_t *client)
{
    char buff[2048] = {0};
    ssize_t len = 0;
    ssize_t nb_read;

    ioctl(client->socket.fd, FIONREAD, &len);
    if (len > 0) {
        nb_read = read(client->socket.fd, buff, len);
        if (nb_read < 1)
            return;
        len -= nb_read;
    }
    launch_cmd(buff, client);
}

void client_loop(client_t client_scks[NB_CLIENT], fd_set fds[FD_COUNT])
{
    for (int i = 0; i < NB_CLIENT; i++) {
        if (FD_ISSET(client_scks[i].socket.fd, &fds[READ])) {
            read_fd(&client_scks[i]);
        }
        if (FD_ISSET(client_scks[i].socket.fd, &fds[WRITE])) {
            write_fd(&client_scks[i]);
        }
    }
}
