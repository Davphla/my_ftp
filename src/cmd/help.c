/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#include "command.h"

void CMD(help)(client_t *client, UNUSED params_t params)
{
    reply(client->socket.fd, HELP, "This is a help message");
}
