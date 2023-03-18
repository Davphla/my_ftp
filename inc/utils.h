/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#pragma once

#include <stdbool.h>

bool safe_cwd(const char *home_path, const char *client_path, const char *path,
    char *new_path);

bool start_data_transfer(const char *new_path, client_t *client,
    char filepath[PATH_MAX]);
