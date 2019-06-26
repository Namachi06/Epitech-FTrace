/*
** EPITECH PROJECT, 2019
** elf.c
** File description:
** Handle ELF
*/

#include "../include/ftrace.h"

int init_elf(t_binary **bin, t_ftrace *ftrace)
{
    *bin = malloc(sizeof(t_binary));
    (*bin)->bin_name = strdup(ftrace->arg);
    if (((*bin)->fd = open((*bin)->bin_name, O_RDONLY)) < 0)
        return (fprintf(stderr, "%s\n", strerror(errno)), ++ftrace->error);
    if (elf_version(EV_CURRENT) == EV_NONE)
        return (fprintf(stderr, elf_errmsg(elf_errno())), ++ftrace->error);
    if (((*bin)->elf = elf_begin((*bin)->fd, ELF_C_READ, NULL)) == NULL)
        return (fprintf(stderr, elf_errmsg(elf_errno())), ++ftrace->error);
    if (elf_kind((*bin)->elf) != ELF_K_ELF)
        return (fprintf(stderr, "%s not an ELF", ftrace->arg), ++ftrace->error);
    if (gelf_getclass((*bin)->elf) == ELFCLASSNONE)
        return (fprintf(stderr, elf_errmsg(elf_errno())), ++ftrace->error);
    return (0);
}

int close_elf(t_binary **bin, t_ftrace *ftrace)
{
    if (elf_end((*bin)->elf) == -1)
        return (fprintf(stderr, elf_errmsg(elf_errno())), ++ftrace->error);
    if (close((*bin)->fd) == -1)
        return (fprintf(stderr, "%s\n", strerror(errno)), ++ftrace->error);
    return (0);
}

void get_shdr(t_binary **bin, Elf_Scn **scn)
{
    Elf64_Shdr *shdr;

    *scn = NULL;
    while ((*scn = elf_nextscn((*bin)->elf, *scn))) {
        if ((shdr = elf64_getshdr(*scn)) == NULL)
            return;
        if (shdr->sh_type == SHT_SYMTAB)
            break;
    }
}

void get_symbols(t_symbols **symbols, t_binary **bin, Elf_Scn *scn)
{
    Elf_Data *data;
    size_t syms_nbr;
    const char *name;

    (*bin)->sym_shdr = elf64_getshdr(scn);
    data = elf_getdata(scn, NULL);
    (*bin)->symtab = (Elf64_Sym *)data->d_buf;
    syms_nbr = (*bin)->sym_shdr->sh_size / (*bin)->sym_shdr->sh_entsize;
    for (size_t i = 0; i < syms_nbr; i++) {
        if (ELF64_ST_TYPE((*bin)->symtab[i].st_info) == STT_FUNC ||
            ELF64_ST_TYPE((*bin)->symtab[i].st_info) == STT_NOTYPE) {
            name = elf_strptr((*bin)->elf, (*bin)->sym_shdr->sh_link,
                (*bin)->symtab[i].st_name);
            add_symbol(symbols, name);
        }
    }
}

int load_symbols(t_symbols **symbols, t_binary **bin, t_ftrace *ftrace)
{
    Elf_Scn	*scn;

    if (init_elf(bin, ftrace) != 0)
        return (++ftrace->error);
    get_shdr(bin, &scn);
    get_symbols(symbols, bin, scn);
    close_elf(bin, ftrace);
    return (ftrace->error);
}