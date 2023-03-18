/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#include "command.h"

void CMD(quit)(client_t *client, UNUSED params_t params)
{
    if (client->connexion_state == CONNECTED) {
        reply(client->socket.fd, LOGGED_OUT, "Logged out. Goodbye !");
        client->connexion_state = NOT_CONNECTED;
    }
    if (client->dfd) {
        reply(client->socket.fd, CLOSING_DATA_CONNECTION,
            "Closing data connection.");
        close(client->dfd);
    }
    close(client->socket.fd);
    client->socket.fd = 0;
}
