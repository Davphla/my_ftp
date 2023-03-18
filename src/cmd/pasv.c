/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#include "client.h"
#include "command.h"
#include <arpa/inet.h>
#include <netinet/in.h>

static char *replace_char(char *str, const char orig, const char rep)
{
    char *new_str = str;

    while (*str) {
        if (*str == orig)
            *str = rep;
        str++;
    }
    return new_str;
}

void CMD(pasv)(client_t *client, UNUSED params_t params)
{
    int port;

    client->socket.socket = BASIC_SOCKET;
    client->socket.len = sizeof(BASIC_SOCKET);
    client->dfd = init_socket(1, &client->socket);
    CATCH_FATAL(getsockname(client->dfd,
        (struct sockaddr *)&client->socket.socket, &client->socket.len));
    port = ntohs(client->socket.socket.sin_port);
    sendfd(client->socket.fd, "%d Entering passive mode (%s,%hu,%hu)",
        ENTERING_PASSIVE_MODE,
        replace_char(inet_ntoa(client->socket.socket.sin_addr), '.', ','),
        port / 256, port % 256);
    client->mode_state = PASSIVE;
}
