/*
** EPITECH PROJECT, 2019
** call_handler.c
** File description:
** Check if it is a Syscall, relative call or indirect call
*/

int is_syscall(int opcode)
{
    opcode &= 0x0000FFFF;
    if (opcode == 0x0000050F)
        return (1);
    return (0);
}

int is_relcall(int opcode)
{
    opcode &= 0xFF;
    if (opcode == 0xE8)
        return (1);
    return (0);
}

int is_indcall(int opcode)
{
    if ((opcode & 0xFF) == 0xFF && (opcode & 0x3800) == 0x1000)
        return (1);
    return (0);
}

int is_call(int opcode)
{
    if (is_syscall(opcode) || is_relcall(opcode) || is_indcall(opcode))
        return (1);
    return (0);
}