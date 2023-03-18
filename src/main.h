/*
** EPITECH PROJECT, 2022
** B-PSU-402-LYN-4-1-strace-david.gozlan
** File description:
** TODO: add description
*/

#pragma once

#include "ftp.h"
#include <getopt.h>

static const struct option long_options[] = {
    {"help", optional_argument, 0, 'h'},
};

static inline void display_usage(const int status)
{
    puts(USAGE);
    exit(status);
}

SINGLETON(int, 0, global)
