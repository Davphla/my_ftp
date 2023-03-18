/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#pragma once

#include "ftp.h"
#include "utils/macro.h"

#define NB_CLIENT 128
#define BUFFER_SIZE 4096

enum client_connection_state_e {
    NOT_CONNECTED = 0,
    USER_SPECIFIED,
    WRONG_USER_SPECIFIED,
    CONNECTED
};

enum client_state_e { NO_MODE = 0, PASSIVE, ACTIVE };

struct buff_s {
    char output_buff[BUFFER_SIZE];
    size_t write_index;
    size_t read_index;
    size_t len;
};

typedef struct client_s {
    socket_t socket;
    int dfd;
    int fork_pid;
    enum client_connection_state_e connexion_state;
    enum client_state_e mode_state;
    char path[PATH_MAX];
    const char *home_path;
    struct buff_s output_buff;
} client_t;

static inline int add_client(const int fd, const size_t size,
    const char *home_path, client_t *list)
{
    for (size_t i = 0; i < size; i++) {
        if (list[i].socket.fd == 0) {
            list[i].socket.fd = fd;
            strcpy(list[i].path, home_path);
            list[i].home_path = home_path;
            return 0;
        }
    }
    return -1;
}

static inline int remove_client(const int fd, const size_t size,
    client_t *list)
{
    for (size_t i = 0; i < size; i++) {
        if (list[i].socket.fd == fd) {
            list[i].socket.fd = 0;
            return 0;
        }
    }
    return -1;
}

static inline int init_socket(const int nb_connections, socket_t *sck)
{
    int fd;

    CATCH_FATAL((fd = socket(AF_INET, SOCK_STREAM, 0)));
    CATCH_FATAL(bind(fd, (struct sockaddr *) &sck->socket, sck->len));
    CATCH_FATAL(listen(fd, nb_connections));
    return fd;
}

static inline void CLEANUP(close)(socket_t *p)
{
    close(p->fd);
}

#define ATTR_CLOSE __attribute__((__cleanup__(CLEANUP(close))))
