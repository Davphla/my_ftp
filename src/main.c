/*
** EPITECH PROJECT, 2022
** B-PSU-402-LYN-4-1-strace-david.gozlan
** File description:
** TODO: add description
*/

#include "main.h"

static void get_flags(const int ac, char *const *av, opt_t *opt)
{
    int option;

    while ((option = getopt_long(ac, av, "h", long_options, NULL)) != EOF) {
        if (option == 'h')
            display_usage(EXIT_SUCCESS);
        else
            display_usage(EXIT_ERROR);
    }
    opt->port = strtol(av[1], NULL, 10);
    if (errno || !realpath(av[2], opt->filepath))
        FATAL();
}

static void start(const int ac, char *const *av)
{
    opt_t opt = {0};

    get_flags(ac, av, &opt);
    main_ftp(&opt);
}

int main(const int ac, char *const *av)
{
    if (ac < 3)
        display_usage(EXIT_ERROR);
    start(ac, av);
    if (g_exit_status)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
