/*
** EPITECH PROJECT, 2019
** ftrace.c
** File description:
** Ftrace
*/

#include "../include/ftrace.h"

void handle_call(t_ftrace *ftrace, struct user_regs_struct *regs,
    unsigned long long int opcode)
{
    int (*check_call[3])(int opcode) = { is_syscall, is_indcall, is_relcall };
    void (*call[3])(t_ftrace *ftrace, struct user_regs_struct *regs) = {
        print_syscall, print_indcall, print_relcall
    };

    for (int i = 0; i < 3; i++) {
        if (check_call[i](opcode))
            call[i](ftrace, regs);
    }
}

int strace_parent(t_ftrace *ftrace, struct user_regs_struct *regs,
    t_binary **bin)
{
    unsigned long long int opcode;
    t_symbols *symbols = NULL;

    if (load_symbols(&symbols, bin, ftrace) != 0)
        return (ftrace->error);
    while (print_signals(ftrace->status)) {
        if (ptrace(PTRACE_GETREGS, ftrace->pid, NULL, regs) == -1)
            return print_ptrace_error();
        opcode = ptrace(PTRACE_PEEKDATA, ftrace->pid, regs->rip, NULL);
        if (errno != 0)
            return print_ptrace_error();
        if (ptrace(PTRACE_SINGLESTEP, ftrace->pid, NULL, NULL) == -1)
            return print_ptrace_error();
        waitpid(ftrace->pid, &ftrace->status, 0);
        if (is_call(opcode))
            handle_call(ftrace, regs, opcode);
    }
    free_symbols(&symbols);
    return (ftrace->error);
}

int handle_ftrace(t_ftrace *ftrace, t_binary **bin, char *argv[])
{
    struct user_regs_struct	regs;

    ftrace->pid = fork();
    if (ftrace->pid == 0) {
        if (ptrace(PTRACE_TRACEME, NULL, NULL, NULL) == -1)
            return print_ptrace_error();
        kill(getpid(), SIGSTOP);
        return execvp(ftrace->arg, argv + 1);
    }
    waitpid(ftrace->pid, &ftrace->status, 0);
    strace_parent(ftrace, &regs, bin);
    return (ftrace->error);
}