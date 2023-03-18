/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#include "main_ftp.h"

static void set_new_client_connection(const opt_t *opt, socket_t *master_sck,
    client_t client_scks[NB_CLIENT], fd_set fds[FD_COUNT])
{
    int cfd;

    if (FD_ISSET(master_sck->fd, &fds[READ])) {
        CATCH_FATAL(
            (cfd = accept(master_sck->fd,
                (struct sockaddr *)&master_sck->socket, &master_sck->len)));
        reply(cfd, NEW_USER, "Welcome user !");
        CATCH_NOT_FATAL(
            add_client(cfd, NB_CLIENT, opt->filepath, client_scks));
    }
}

static void reset_client_sockets(client_t *client_scks, fd_set *fds, int *max)
{
    int cur_fd;

    for (size_t j = 0; j < NB_CLIENT; j++) {
        cur_fd = client_scks->socket.fd;
        if (cur_fd > 0) {
            FD_SET(cur_fd, fds);
        }
        if (cur_fd > *max) {
            *max = cur_fd;
        }
    }
}

static int reset_fds(const int sfd, client_t client_scks[NB_CLIENT],
    fd_set fds[FD_COUNT])
{
    int max = 0;

    for (size_t i = 0; i < FD_COUNT; i++) {
        FD_ZERO(&fds[i]);
        FD_SET(sfd, &fds[i]);
        reset_client_sockets(&client_scks[i], &fds[i], &max);
    }
    return max;
}

void main_ftp(const opt_t *opt)
{
    fd_set fds[FD_COUNT];
    int max_sfd;
    client_t client_scks[NB_CLIENT] = {0};
    socket_t ATTR_CLOSE master_sck = {
        .socket = BASIC_SOCKET,
        .len = sizeof(master_sck.socket),
    };

    master_sck.socket.sin_port = htons(opt->port);
    master_sck.fd = init_socket(3, &master_sck);
    while (true) {
        max_sfd = reset_fds(master_sck.fd, client_scks, fds);
        CATCH_FATAL(select((max_sfd ?: master_sck.fd) + 1, &fds[READ],
            &fds[WRITE], &fds[EXCEPTION], NULL));
        set_new_client_connection(opt, &master_sck, client_scks, fds);
        client_loop(client_scks, fds);
    }
}
