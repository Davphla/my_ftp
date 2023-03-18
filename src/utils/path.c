/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool safe_cwd(const char *home_path, const char *client_path, const char *path,
    char *new_path)
{
    char filepath[PATH_MAX] = {0};

    if (!path)
        return true;
    if (*path == '/') {
        snprintf(filepath, PATH_MAX, "%s", path);
    } else {
        snprintf(filepath, PATH_MAX, "%s/%s", client_path, path);
    }
    if (realpath(filepath, new_path) == NULL
        || strstr(new_path, home_path) == NULL) {
        return true;
    }
    return false;
}
