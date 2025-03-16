/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:55:46 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/16 14:45:35 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_list *tokens)
{
	t_token	*token;

	token = (t_token *)tokens->content;
	printf("TOKEN: Type=%d, Value=%s\\0\n", token->type, token->value);
}

void	print_list(t_list *list)
{
	ft_printf("%s\n", list->content);
}

void	print_string_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_printf("%s\n", arr[i]);
		i++;
	}
}

void	print_export(char **env)
{
	char	*value;
	char	*copy;
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		copy = ft_strdup_gc(env[i]);
		value = ft_strchr(copy, '=');
		if (value)
		{
			*value = '\0';
			value++;
			ft_printf("declare -x %s=\"%s\"\n", copy, value);
		}
		else
			ft_printf("declare -x %s\n", copy);
		gc_free_one(copy);
		i++;
	}
}
