/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:57:20 by cwolf             #+#    #+#             */
/*   Updated: 2025/03/16 14:57:45 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_list_remove(t_list **begin_list)
{
	t_list	*remove;
	t_list	*current;
	t_token	*token;

	current = *begin_list;
	while (current && current->next)
	{
		token = (t_token *)current->next->content;
		if (ft_strlen(token->value) == 0)
		{
			remove = current->next;
			current->next = current->next->next;
			gc_free_one(remove);
		}
		current = current->next;
	}
	current = *begin_list;
	token = (t_token *)current->content;
	if (current && ft_strlen(token->value) == 0)
	{
		*begin_list = current->next;
		gc_free_one(current);
	}
}
