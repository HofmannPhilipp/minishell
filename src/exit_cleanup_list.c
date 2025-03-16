/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cleanup_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:05:25 by cwolf             #+#    #+#             */
/*   Updated: 2025/03/16 15:49:58 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ecl_manager	*get_ecl_instance(void)
{
	static t_ecl_manager	ecl = {NULL};

	return (&ecl);
}

void	*ecl_alloc(int size)
{
	void			*ptr;
	t_gc_node		*node;
	t_ecl_manager	*ecl;

	ecl = get_ecl_instance();
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
	node->next = ecl->head;
	ecl->head = node;
	return (ptr);
}

void	ecl_free_all(void)
{
	t_gc_node		*node;
	t_gc_node		*next;
	t_ecl_manager	*ecl;

	ecl = get_ecl_instance();
	node = ecl->head;
	while (node)
	{
		next = node->next;
		free(node->ptr);
		free(node);
		node = next;
	}
	ecl->head = NULL;
}

void	ecl_free_one(void *ptr)
{
	t_ecl_manager	*ecl;
	t_gc_node		*prev;
	t_gc_node		*curr;

	ecl = get_ecl_instance();
	prev = NULL;
	curr = ecl->head;
	while (curr)
	{
		if (curr->ptr == ptr)
		{
			if (prev)
				prev->next = curr->next;
			else
				ecl->head = curr->next;
			free(curr->ptr);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
	ft_printf("Warning: Trying to free ptr not in ecl list\n");
}
