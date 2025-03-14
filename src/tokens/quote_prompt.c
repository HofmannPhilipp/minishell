/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:35:24 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/13 16:13:15 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	found_closing_quote(char *str, char qoute_type)
{
	int	i;
	int	qoute_count;
	
	i = 0;
	qoute_count = 1;
	while (str[i])
	{
		if (str[i] == qoute_type)
			qoute_count ++;
		i++;
	}
	if (qoute_count % 2 == 0)
		return (1);
	return (0);
}

char	*open_quote_prompt(char *prompt, char qoute_type)
{
	char	*result;
	char	*temp;
	char	*input;
	
	result = ft_strdup_gc(prompt);
	while (1)
	{
		if (qoute_type == '"')
			input = readline("dquote> ");
		else
			input = readline("qoute> ");
		temp = ft_strjoin_gc("\n", input);
		free(input);
		input = ft_strjoin_gc(result, temp);
		gc_free_one(temp);
		gc_free_one(result);
		result = input;
		if (found_closing_quote(result, qoute_type) == 1)
			break;
	}
	return (result);
}