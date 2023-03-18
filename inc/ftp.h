/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#pragma once

#include "utils/error.h"
#include "utils/macro.h"
#include <linux/limits.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define USAGE                                                                 \
    "USAGE: ./myftp [Port] [Path]\n"                                          \
    "   Port is the port number on which the server socket listens\n"         \
    "   Path is the path to the home directory for the Anonymous user\n"

#define CLRF "\r\n"

typedef struct opt_s {
    unsigned int port;
    char filepath[PATH_MAX];
} opt_t;

typedef struct socket_s {
    int fd;
    struct sockaddr_in socket;
    socklen_t len;
} socket_t;

void main_ftp(const opt_t *opt);

enum fds_e { READ, WRITE, EXCEPTION };

#define FD_COUNT 3

static const struct sockaddr_in BASIC_SOCKET = {.sin_family = AF_INET,
    .sin_addr.s_addr = INADDR_ANY,
    .sin_port = 0};
