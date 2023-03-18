/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#include "command.h"

void CMD(pwd)(client_t *client, UNUSED params_t params)
{
    sendfd(client->socket.fd, "257 %s is the current directory", client->path);
}
