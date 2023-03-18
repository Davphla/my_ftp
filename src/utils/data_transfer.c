/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#include "command.h"
#include "utils.h"

static void check_mode(client_t *client)
{
    switch (client->mode_state) {
        case PASSIVE:
            CATCH_FATAL((client->dfd = accept(client->dfd,
                            (struct sockaddr *)&client->socket.socket,
                            &client->socket.len)));
            break;
        case ACTIVE:
            CATCH_FATAL((client->dfd = connect(client->dfd,
                            (struct sockaddr *)&client->socket.socket,
                            client->socket.len)));
            break;
        default: break;
    }
}

bool start_data_transfer(const char *new_path, client_t *client,
    char filepath[PATH_MAX])
{
    int pid;

    if (client->mode_state == NO_MODE) {
        reply(client->socket.fd, 425, "Use PORT or PASV first.");
        return true;
    }
    if (safe_cwd(client->home_path, client->path, new_path, filepath))
        return true;
    pid = fork();
    if (pid) {
        client->fork_pid = pid;
        return true;
    }
    check_mode(client);
    reply(client->socket.fd, TRANSFER,
        "Data connection open, transfer starting.");
    return false;
}
