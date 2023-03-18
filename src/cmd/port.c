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

void CMD(port)(client_t *client, UNUSED params_t params)
{
    int dfd;

    client->socket.socket = BASIC_SOCKET;
    client->socket.len = sizeof(BASIC_SOCKET);
    CATCH_FATAL((dfd = socket(AF_INET, SOCK_STREAM, 0)));
    CATCH_FATAL(
        connect(dfd, (struct sockaddr *)&BASIC_SOCKET, sizeof(BASIC_SOCKET)));
    reply(client->socket.fd, OKAY, "Command successful.");
    client->dfd = dfd;
}
