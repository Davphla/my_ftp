/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#include "command.h"

void CMD(user)(client_t *client, params_t params)
{
    if (params && client->connexion_state == NOT_CONNECTED) {
        if (strncmp(params, "Anonymous", 9) == 0) {
            client->connexion_state = USER_SPECIFIED;
        } else {
            client->connexion_state = WRONG_USER_SPECIFIED;
        }
        reply(client->socket.fd, USERNAME_OKAY,
            "Please specify the password.");
    } else {
        reply(client->socket.fd, USERNAME_OKAY,
            "Wrong Authentication test failed");
    }
}
