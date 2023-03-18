/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#include "command.h"
#include "utils.h"
#include <sys/ioctl.h>

UNUSED static bool read_and_write_file(const client_t *client,
    const char *filepath)
{
    size_t size;
    char ATTR_FREE *file_content;
    FILE ATTR_FCLOSE *fd = fopen(filepath, "w");

    ioctl(client->socket.fd, FIONREAD, &size);
    fread(file_content, sizeof(char), size, fd);
    file_content = malloc(sizeof(char) * (size + 1));
    if (fread(file_content, sizeof(char), size, fd) == size) {
        dprintf(client->dfd, "%s", file_content);
        return true;
    }
    NOT_FATAL("%s (%zu)", filepath, size);
    return false;
}

void CMD(stor)(client_t *client, UNUSED params_t params)
{
    char filepath[PATH_MAX];

    if (start_data_transfer(params, client, filepath))
        return;
    close(client->dfd);
    client->dfd = 0;
    exit(EXIT_SUCCESS);
}
