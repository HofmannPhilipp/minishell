/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_collec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:05:17 by cwolf             #+#    #+#             */
/*   Updated: 2025/03/13 15:30:23 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void gc_print_list(void)
{
    t_gc_manager *gc = get_gc_instance();
    t_gc_node *current = gc->head;

    if (!current)
    {
        ft_printf("Garbage Collector List is empty.\n");
        return;
    }

    ft_printf("Garbage Collector List:\n");
    while (current)
    {
        ft_printf("Allocated memory at: %p\n", current->ptr);
        current = current->next;
    }
}
t_gc_manager* get_gc_instance()
{
    static t_gc_manager gc = {NULL};
    return (&gc);
}

void *gc_alloc(int size)
{
    void *ptr;
    t_gc_node *node;
    t_gc_manager *gc;
    
    gc = get_gc_instance();
	ptr = malloc(size);
    if (!ptr)
	{
		gc_free_all();
		ecl_free_all();
        panic("malloc failed");
    }
	node = malloc(sizeof(t_gc_node));
    if (!node)
	{
        free(ptr);	
		gc_free_all();
		ecl_free_all();
        panic("malloc failed");
    }
    node->ptr = ptr;
    node->next = gc->head;
    gc->head = node;

    return (ptr);
}

void gc_free_all(void) 
{
    t_gc_node *node;
	t_gc_node *next;
    t_gc_manager    *gc;

    gc = get_gc_instance();
	node = gc->head;
    // ft_printf("FREE_ALL FUNCTION .........\n");
    while (node) 
	{
        next = node->next;
        free(node->ptr);
        free(node);
        node = next;
    }
    gc->head = NULL;
}

void gc_free_one(void *ptr)
{
    t_gc_manager *gc;
    t_gc_node *prev;
    t_gc_node *curr;

    gc = get_gc_instance();
    prev = NULL;
    curr = gc->head;
    
    while (curr)
    {
        if (curr->ptr == ptr)
        {
            if (prev)
                prev->next = curr->next;
            else
                gc->head = curr->next;
            free(curr->ptr);
            free(curr);
            return ;
        }
        prev = curr;
        curr = curr->next;
    }
    ft_printf("Warning: Trying to free ptr not in gc list\n");
}