/*
** EPITECH PROJECT, 2019
** print_syscalls.c
** File description:
** Print syscalls
*/

/*
** EPITECH PROJECT, 2019
** print_syscall.c
** File description:
** print_syscall
*/

#include "../../../include/ftrace.h"
#include "../../../include/syscalls.h"

void print_return_value(t_syscall *syscall, struct user_regs_struct *regs,
    t_ftrace *ftrace)
{
    if (syscall->return_type == VOID) {
        printf(" = ?\n");
        return;
    }
    ptrace(PTRACE_SINGLESTEP, ftrace->pid, NULL, NULL);
    waitpid(ftrace->pid, &ftrace->status, 0);
    ptrace(PTRACE_GETREGS, ftrace->pid, NULL, regs);
    printf(" = 0x%llx\n", regs->rax);
}

void print_addresses(t_syscall *syscall, struct user_regs_struct *regs,
    t_ftrace *ftrace)
{
    void (*print_args[7])(struct user_regs_struct *regs) = { print_1,
        print_2, print_3, print_4, print_5, print_6, print_7 };
    for (int i = 0; i < 7; i++) {
        if (syscall->nb_args == i)
            print_args[i - 1](regs);
    }
    print_return_value(syscall, regs, ftrace);
}

void get_syscall(t_syscall **syscall, struct user_regs_struct *regs)
{
    int i = 0;

    for (; syscalls[i].id != -1 && (int)regs->rax != syscalls[i].id; i++);
    if (syscalls[i].id != -1 || (int)regs->rax == syscalls[i].id)
        *syscall = &syscalls[i];
    else
        *syscall = NULL;
}

void print_syscall(t_ftrace *ftrace, struct user_regs_struct *regs)
{
    t_syscall *syscall;

    get_syscall(&syscall, regs);
    if (syscall == NULL)
        return;
    printf("Syscall %s", syscall->name);
    print_addresses(syscall, regs, ftrace);
}