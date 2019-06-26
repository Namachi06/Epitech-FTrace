/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** Main programm
*/

#include "../include/ftrace.h"

void print_usage(void)
{
    fprintf(stderr, "USAGE: ftrace <command>\n");
}

int main(int argc, char *argv[])
{
    t_ftrace ftrace;
    t_binary *bin;

    if (check_args(argc, argv, &ftrace) != 0) {
        free_ftrace(&ftrace);
        return (84);
    }
    if (handle_ftrace(&ftrace, &bin, argv) != 0)
        return (84);
    if (free_bin(&bin, ftrace) != 0)
        return (84);
    free_ftrace(&ftrace);
    return (0);
}
