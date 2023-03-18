/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#include "command.h"
#include "utils.h"

static bool read_file_and_transfer(const client_t *client,
    const char *filepath)
{
    size_t size;
    char ATTR_FREE *file_content;
    FILE ATTR_FCLOSE *fd = fopen(filepath, "r");

    fseek(fd, 0L, SEEK_END);
    size = ftell(fd);
    file_content = malloc(sizeof(char) * (size + 1));
    fseek(fd, 0, SEEK_SET);
    if (fread(file_content, sizeof(char), size, fd) == size) {
        dprintf(client->dfd, "%s", file_content);
        return true;
    }
    NOT_FATAL("%s (%zu)", filepath, size);
    return false;
}

void CMD(retr)(client_t *client, UNUSED params_t params)
{
    char filepath[PATH_MAX];

    if (start_data_transfer(params, client, filepath))
        return;
    if (read_file_and_transfer(client, filepath)) {
        reply(client->socket.fd, 150,
            "Requested file action okay, completed.");
    } else {
        reply(client->socket.fd, 550, "Failed to open file.");
    }
    close(client->dfd);
    client->dfd = 0;
    exit(EXIT_SUCCESS);
}
