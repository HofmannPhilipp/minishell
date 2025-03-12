/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 08:58:01 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/11 16:00:53 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	found_delimeter(char *str, char *delimeter)
{
	if (ft_strncmp(str, delimeter, ft_strlen(delimeter)) == 0)
		return (1);
	return (0);
}

char	*open_heredoc_prompt(char *delimeter)
{
	char	*result;
	char	*temp;
	char	*input;

	result = ft_strdup_gc("");
	while(1)
	{
		input = readline("heredoc> ");
		if (found_delimeter(input, delimeter) == 1)
		{
			break;
		}
		temp = ft_strjoin_gc(input, "\n");
		// free(input);
		input = ft_strjoin_gc(result, temp);
		// gc_free_one(temp);
		// free(result);
		result = input;
	}
	return (result);
}