/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#pragma once

#include "client.h"
#include "ftp.h"

enum reply_code_e {
    READY = 120,
    TRANSFER = 125,
    FILE_STATUS_OK = 150,
    OKAY = 200,
    HELP = 214,
    NEW_USER = 220,
    LOGGED_OUT = 221,
    CLOSING_DATA_CONNECTION = 226,
    ENTERING_PASSIVE_MODE = 227,
    USER_LOGGED_IN = 230,
    FILE_ACTION = 250,
    PATHNAME_CREATED = 257,
    USERNAME_OKAY = 331,
    NEED_ACCOUNT = 332,
};

#define CMD(cmd) cmd_##cmd

typedef char params_t[BUFFER_SIZE];

// Prototypes
void CMD(cdup)(client_t *, params_t);
void CMD(cwd)(client_t *, params_t);
void CMD(dele)(client_t *, params_t);
void CMD(help)(client_t *, params_t);
void CMD(list)(client_t *, params_t);
void CMD(noop)(client_t *, params_t);
void CMD(pass)(client_t *, params_t);
void CMD(pasv)(client_t *, params_t);
void CMD(port)(client_t *, params_t);
void CMD(pwd)(client_t *, params_t);
void CMD(quit)(client_t *, params_t);
void CMD(retr)(client_t *, params_t);
void CMD(stor)(client_t *, params_t);
void CMD(user)(client_t *, params_t);

static const struct commands_s {
    const char *cmd;
    void (*cmd_ptr)(client_t *, params_t);
    bool need_authentication;
} CMD_CONST[] = {{"CDUP", &CMD(cdup), true}, {"CWD", &CMD(cwd), true},
    {"DELE", &CMD(dele), true}, {"HELP", &CMD(help), false},
    {"LIST", &CMD(list), true}, {"NOOP", &CMD(noop), false},
    {"PASS", &CMD(pass), false}, {"PASV", &CMD(pasv), true},
    {"PORT", &CMD(port), true}, {"PWD", &CMD(pwd), true},
    {"QUIT", &CMD(quit), false}, {"RETR", &CMD(retr), true},
    {"STOR", &CMD(stor), true}, {"USER", &CMD(user), false}};

static inline void reply(const int fd, const int reply_code,
    const char *message)
{
    if (reply_code) {
        CATCH_NOT_FATAL(dprintf(fd, "%d (%s)" CLRF, reply_code, message));
    } else {
        CATCH_NOT_FATAL(dprintf(fd, "xxx (%s)" CLRF, message));
    }
}

static inline void sendfd(const int fd, const char *message, ...)
{
    va_list args;

    va_start(args, message);
    CATCH_NOT_FATAL(vdprintf(fd, message, args));
    CATCH_NOT_FATAL(dprintf(fd, "%s", CLRF));
}

static inline void CLEANUP(dclient)(client_t *p)
{
    close(p->dfd);
    p->dfd = 0;
}

#define ATTR_DSOCKET __attribute__((__cleanup__(CLEANUP(dclient))))
