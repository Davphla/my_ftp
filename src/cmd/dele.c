/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#include "command.h"
#include "utils.h"

void CMD(dele)(client_t *client, UNUSED params_t params)
{
    char filepath[PATH_MAX] = {0};

    if (safe_cwd(client->home_path, client->path, params, filepath)) {
        NOT_FATAL();
        return reply(client->socket.fd, 550, "Delete operation failed.");
    }
    if (remove(filepath) != -1) {
        reply(client->socket.fd, FILE_ACTION,
            "Requested file action okay, completed.");
    } else {
        reply(client->socket.fd, 550, "Failed to open file.");
    }
}
