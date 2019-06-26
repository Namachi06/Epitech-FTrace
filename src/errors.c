/*
** EPITECH PROJECT, 2019
** errors.c
** File description:
** Error printing
*/

#include "../include/ftrace.h"

int print_ptrace_error(void)
{
    fprintf(stderr, "ptrace: Fail");
    return (-1);
}