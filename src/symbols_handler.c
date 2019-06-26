/*
** EPITECH PROJECT, 2019
** symbols_handler.c
** File description:
** Create or delete symbols
*/

#include "../include/ftrace.h"

void add_symbol(t_symbols **symbols, const char *name)
{
    t_symbols *new_node = malloc(sizeof(t_symbols));
    t_symbols *last = *symbols;

    new_node->name = strdup(name);
    new_node->next = NULL;
    if (*symbols == NULL) {
        *symbols = new_node;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
}

void free_symbols(t_symbols **symbols)
{
    t_symbols *tmp;

    while (*symbols != NULL) {
        tmp = *symbols;
        free(tmp->name);
        *symbols = (*symbols)->next;
        free(tmp);
    }
}