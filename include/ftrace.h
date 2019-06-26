/*
** EPITECH PROJECT, 2019
** ftrace.h
** File description:
** Ftrace header
*/

#ifndef FTRACE_H_
    #define FTRACE_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <signal.h>
#include <sys/reg.h>
#include <errno.h>
#include <libelf.h>
#include <gelf.h>

typedef struct s_symbols
{
    char *name;
    struct s_symbols *next;
} t_symbols;

typedef struct s_binary
{
    int fd;
    char *bin_name;
    Elf *elf;
    Elf64_Sym *symtab;
    Elf64_Shdr *sym_shdr;
    Elf64_Sym *dynsym_tab;
} t_binary;

typedef struct s_ftrace
{
    int error;
    int status;
    pid_t pid;
    char *arg;
} t_ftrace;

// main.c
void print_usage(void);

// handle_args.c
int check_args(int argc, char *argv[], t_ftrace *ftrace);

// sym_name.c
int load_symbols(t_symbols **symbols, t_binary **bin, t_ftrace *ftrace);

// symbols_handler.c
void add_symbol(t_symbols **symbols, const char *name);
void free_symbols(t_symbols **symbols);

// ftrace.c
int handle_ftrace(t_ftrace *ftrace, t_binary **bin, char *argv[]);

// print_signals.c
int print_signals(int status);

// call_handler.c
int is_call(int opcode);
int is_indcall(int opcode);
int is_relcall(int opcode);
int is_syscall(int opcode);

// print_syscalls.c
void print_syscall(t_ftrace *ftrace, struct user_regs_struct *regs);

// print_args_addresses.c
void print_1(struct user_regs_struct *regs);
void print_2(struct user_regs_struct *regs);
void print_3(struct user_regs_struct *regs);
void print_4(struct user_regs_struct *regs);
void print_5(struct user_regs_struct *regs);
void print_6(struct user_regs_struct *regs);
void print_7(struct user_regs_struct *regs);

// print_indcall.c
void print_indcall(t_ftrace *ftrace, struct user_regs_struct *regs);

// print_relcall.c
void print_relcall(t_ftrace *ftrace, struct user_regs_struct *regs);

// errors.c
int print_ptrace_error(void);

// free.c
void free_ftrace(t_ftrace *ftrace);
int free_bin(t_binary **bin, t_ftrace ftrace);

#endif /* !FTRACE_H_ */
