/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#include "command.h"

void CMD(pass)(client_t *client, UNUSED params_t params)
{
    switch (client->connexion_state) {
        case NOT_CONNECTED:
            reply(client->socket.fd, 503, "Login with USER first.");
            break;
        case WRONG_USER_SPECIFIED:
            reply(client->socket.fd, 530, "Login incorrect.");
            client->connexion_state = NOT_CONNECTED;
            break;
        case USER_SPECIFIED:
            client->connexion_state = CONNECTED;
            reply(client->socket.fd, USER_LOGGED_IN,
                "User logged in, proceed.");
            break;
        case CONNECTED:
            reply(client->socket.fd, 530, "Can't change to another user.");
            break;
    }
}
