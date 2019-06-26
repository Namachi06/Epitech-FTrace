/*
** EPITECH PROJECT, 2019
** print_args_addresses.c
** File description:
** Print the correct number of arguments
*/

#include "../../../include/ftrace.h"

void print_1(struct user_regs_struct *regs)
{
    printf("(0x%llx)", regs->rdi);
}

void print_2(struct user_regs_struct *regs)
{
    printf("(0x%llx, 0x%llx)", regs->rdi, regs->rsi);
}

void print_3(struct user_regs_struct *regs)
{
    printf("(0x%llx, 0x%llx, 0x%llx)", regs->rdi, regs->rsi, regs->rdx);
}

void print_4(struct user_regs_struct *regs)
{
    printf("(0x%llx, 0x%llx, 0x%llx, 0x%llx)", regs->rdi, regs->rsi,
        regs->rdx, regs->r8);
}

void print_5(struct user_regs_struct *regs)
{
    printf("(0x%llx, 0x%llx, 0x%llx, 0x%llx, 0x%llx)", regs->rdi, regs->rsi,
        regs->rdx, regs->r8, regs->r9);
}