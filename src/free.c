/*
** EPITECH PROJECT, 2019
** free.c
** File description:
** Free
*/

#include "../include/ftrace.h"

void free_ftrace(t_ftrace *ftrace)
{
    if (!ftrace)
        return;
    if (ftrace->arg)
        free(ftrace->arg);
}

int free_bin(t_binary **bin, t_ftrace ftrace)
{
    if (!(*bin))
        return (0);
    if ((*bin)->fd == 0)
        return ++ftrace.error;
    if ((*bin)->bin_name)
        free((*bin)->bin_name);
    free((*bin));
    return (0);
}