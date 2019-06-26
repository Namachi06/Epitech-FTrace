/*
** EPITECH PROJECT, 2019
** print_signals.c
** File description:
** Print signals
*/

#include "../include/ftrace.h"
#include "../include/signals.h"

char *get_sig(int sig)
{
    int i = 0;

    for (; signals[i].id != -1; i++) {
        if (signals[i].id == sig)
            return signals[i].sig_name;
    }
    return signals[++i].sig_name;
}

int print_signals(int status)
{
    if (WIFEXITED(status))
        return (printf("+++ exited with %i +++\n", WEXITSTATUS(status)), 0);
    else if (WIFSTOPPED(status)) {
        if (WSTOPSIG(status) != SIGTRAP && WSTOPSIG(status) != SIGSTOP)
            return (printf("Received signal %s\n", get_sig(WSTOPSIG(status))),
                0);
    }
    else if (WIFSIGNALED(status))
        return (printf("Received signal %s\n", get_sig(WTERMSIG(status))), 0);
    return (42);
}