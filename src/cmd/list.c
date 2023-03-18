/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#include "command.h"
#include <dirent.h>
#include "utils.h"

static int print_directory(const int fd, const char *directory)
{
    DIR *d;
    struct dirent *dir;

    if (access(directory, F_OK) || (d = opendir(directory)) == NULL) {
        NOT_FATAL();
        return 1;
    }
    while ((dir = readdir(d)) != NULL) {
        dprintf(fd, "%s ", dir->d_name);
    }
    sendfd(fd, "");
    closedir(d);
    return 0;
}

static int print_multiple_directory(const int fd, params_t params)
{
    char *directory = strtok(params, " ");

    do {
        dprintf(fd, "%s\n", directory);
        if (print_directory(fd, directory))
            return 1;
        dprintf(fd, "\n");
        directory = strtok(NULL, " ");
    } while (directory);
    return 0;
}

void CMD(list)(UNUSED client_t *client, params_t params)
{
    char filepath[PATH_MAX];
    int error;

    if (start_data_transfer(params, client, filepath))
        return;
    reply(client->socket.fd, 150, "Here comes the directory listing.");
    if (params) {
        error = print_multiple_directory(client->dfd, params);
    } else {
        error = print_directory(client->dfd, client->path);
    }
    if (!error) {
        reply(client->socket.fd, 257, "Directory send OK.");
    } else {
        reply(client->socket.fd, 550, "Failed to open file.");
    }
    close(client->dfd);
    client->dfd = 0;
    exit(EXIT_SUCCESS);
}
