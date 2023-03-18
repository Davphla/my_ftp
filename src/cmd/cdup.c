/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#include "command.h"

void CMD(cdup)(client_t *client, UNUSED params_t params)
{
    strcpy(client->path, client->home_path);
    reply(client->socket.fd, 250, "Directory successfully changed.");
}
