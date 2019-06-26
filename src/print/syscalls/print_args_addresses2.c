/*
** EPITECH PROJECT, 2019
** print_args_addresses2.c
** File description:
** Print the correct number of arguments
*/

#include "../../../include/ftrace.h"

void print_6(struct user_regs_struct *regs)
{
    printf("(0x%llx, 0x%llx, 0x%llx, 0x%llx, 0x%llx, 0x%llx)", regs->rdi,
        regs->rsi, regs->rdx, regs->r8, regs->r9, regs->r10);
}

void print_7(struct user_regs_struct *regs)
{
    printf("(0x%llx, 0x%llx, 0x%llx, 0x%llx, 0x%llx, 0x%llx, 0x%llx)",
        regs->rdi, regs->rsi, regs->rdx, regs->r8, regs->r9, regs->r10,
        regs->r11);
}