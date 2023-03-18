/*
** EPITECH PROJECT, 2022
** B-PSU-402-LYN-4-1-strace-david.gozlan
** File description:
** TODO: add description
*/

#pragma once

#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdlib.h>

#define SINGLETON(t, init, name)                                              \
    t *s_##name()                                                             \
    {                                                                         \
        static t inst = init;                                                 \
        return &inst;                                                         \
    }

#define LEN(a) (sizeof(a) / sizeof(a)[0])

#define FOREACH(NAME, DATA, SIZE)                                             \
    for (__typeof__(*(DATA)) *(NAME) = &(DATA)[0]; (NAME) < &(DATA)[(SIZE)];  \
         (NAME)++)

static inline void cleanup_free(void *p)
{
    free(*(void **) p);
}

#define ATTR_FREE __attribute__((__cleanup__(cleanup_free)))

#define LAMBDA(return_value, params, expression)                              \
    ({                                                                        \
        return_value lambda_func params expression;                           \
        &lambda_func;                                                         \
    })

#define UNUSED __attribute__((unused))

#define CLEANUP(name) cleanup_##name

static inline void CLEANUP(fclose)(FILE **fd)
{
    fclose(*fd);
}

#define ATTR_FCLOSE __attribute__((__cleanup__(CLEANUP(fclose))))
