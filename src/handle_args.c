/*
** EPITECH PROJECT, 2019
** handle_args.c
** File description:
** Handle arguments and errors
*/

#include "../include/ftrace.h"
#include "../include/my.h"

int free_env(char **env, char *path, int free_path)
{
    if (free_path)
        free(path);
    if (env == NULL)
        return -1;
    for (int i = 0; env[i]; i++)
        free(env[i]);
    free(env);
    return (0);
}

void init_struct_strace(t_ftrace *ftrace)
{
    ftrace->error = 0;
    ftrace->status = 0;
    ftrace->pid = 0;
    ftrace->arg = NULL;
}

int check_bin(t_ftrace *ftrace)
{
    if (access(ftrace->arg, X_OK) != -1)
        return (ftrace->error);
    return (ftrace->error);
}

int check_args(int argc, char *argv[], t_ftrace *ftrace)
{
    init_struct_strace(ftrace);
    if (argc < 2) {
        print_usage();
        return (++ftrace->error);
    }
    ftrace->arg = strdup(argv[1]);
    check_bin(ftrace);
    return (ftrace->error);
}