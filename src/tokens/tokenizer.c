/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:10:07 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/16 14:10:03 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	is_symbol(char *str, int in_quotes)
{
	if (in_quotes != 0)
		return ('a');
	if (str[0] == '\0')
		return ('\0');
	if (str[0] == '>' && str[1] == '>')
		return ('+');
	if (str[0] == '<' && str[1] == '<')
		return ('#');
	if (ft_strchr("();|&<>", str[0]) == NULL)
		return ('a');
	return (str[0]);
}

void	skip_whitespace(char **prompt)
{
	while (ft_strchr("\t\n\v\f\r ", **prompt) != NULL && **prompt != '\0')
		(*prompt)++;
}

t_list	*tokenizer(char *prompt, char **envp)
{
	t_list	*tokens;
	t_list	*node;

	if (!prompt)
		return (NULL);
	tokens = NULL;
	while (*prompt != '\0')
	{
		skip_whitespace(&prompt);
		if (*prompt == '\0')
			break ;
		if (is_symbol(prompt, 0) == '#')
			node = parse_heredoc(&prompt);
		else if (is_symbol(prompt, 0) == 'a')
			node = parse_text(&prompt, envp);
		else
			node = parse_operator(&prompt);
		ft_lstadd_back(&tokens, node);
	}
	return (tokens);
}

int	get_token_type(char c)
{
	if (c == '#')
		return (HERE_DOC);
	if (c == '<' || c == '>' || c == '+')
		return (REDIR);
	if (c == '|')
		return (PIPE);
	if (c == ';')
		return (SEQ);
	if (c == '&')
		return (BACK);
	if (c == '(' || c == ')')
		return (PARENS);
	return (TEXT);
}
