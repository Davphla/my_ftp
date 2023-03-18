/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#include "command.h"
#include "utils.h"

void CMD(cwd)(client_t *client, params_t params)
{
    char filepath[PATH_MAX];

    if (safe_cwd(client->home_path, client->path, params, filepath)) {
        NOT_FATAL();
        return reply(client->socket.fd, 550, "Failed to change directory.");
    }
    if (chdir(filepath) == -1) {
        NOT_FATAL("%s", filepath);
        return;
    }
    strncpy(client->path, filepath, LEN(filepath));
    reply(client->socket.fd, 250, "Directory successfully changed.");
}
