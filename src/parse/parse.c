/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:49:05 by phhofman          #+#    #+#             */
/*   Updated: 2025/02/05 15:49:54 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*read_prompt()
{
	char	*prompt;
	char	*input;
	
	prompt = "🤏🐚\033[0;32m $ \033[0m";

	input = readline(prompt);
	add_history(input);

	return (input);
}