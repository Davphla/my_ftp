/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#include "command.h"

void CMD(noop)(UNUSED client_t *client, UNUSED params_t params)
{
    reply(client->socket.fd, OKAY, "NOOP ok.");
}
