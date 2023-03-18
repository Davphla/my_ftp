/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#pragma once

#include "client.h"
#include "command.h"
#include "ftp.h"
#include <netinet/in.h>
#include <sys/socket.h>

void client_loop(client_t client_scks[NB_CLIENT], fd_set fds[FD_COUNT]);
