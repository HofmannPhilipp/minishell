/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cleanup_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:05:25 by cwolf             #+#    #+#             */
/*   Updated: 2025/03/13 10:29:19 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ecl_manager* get_ecl_instance()
{
    static t_ecl_manager ecl = {NULL};
    return (&ecl);
}

void *ecl_alloc(int size)
{
    void *ptr;
    t_gc_node *node;
    t_ecl_manager *ecl;
    
    ecl = get_ecl_instance();
	ptr = malloc(size);
    if (!ptr)
	{
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
	node = malloc(sizeof(t_gc_node));
    if (!node)
	{
        perror("malloc failed");
        free(ptr);	
        exit(EXIT_FAILURE);
    }
    node->ptr = ptr;
    node->next = ecl->head;
    ecl->head = node;

    return (ptr);
}

void ecl_free_all(void) 
{
    t_gc_node *node;
	t_gc_node *next;
    t_ecl_manager    *ecl;

    ecl = get_ecl_instance();
	node = ecl->head;
    // ft_printf("FREE_ALL FUNCTION .........\n");
    while (node) 
	{
        next = node->next;
        free(node->ptr);
        free(node);
        node = next;
    }
    ecl->head = NULL;
}
