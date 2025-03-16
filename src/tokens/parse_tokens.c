/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:59:47 by cwolf             #+#    #+#             */
/*   Updated: 2025/03/16 14:14:12 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_qoutes(char **prompt, char quote_type, char **envp)
{
	int		token_len;
	char	*result;

	token_len = 0;
	(*prompt)++;
	while (**prompt != '\0' && **prompt != quote_type)
	{
		token_len++;
		(*prompt)++;
	}
	result = ft_substr_gc(*prompt - token_len, 0, token_len);
	if (**prompt != quote_type)
	{
		result = open_quote_prompt(result, quote_type);
		return (result);
	}
	if (quote_type == '"')
		result = expand_str(result, envp);
	(*prompt)++;
	return (result);
}

static int	get_token_len(char **prompt)
{
	int	token_len;

	token_len = 0;
	while (**prompt != '\0')
	{
		if ((**prompt == '"' || **prompt == '\'') || \
			(ft_strchr("\t\n\v\f\r ", **prompt) || is_symbol(*prompt, \
			0) != 'a'))
			break ;
		(*prompt)++;
		token_len++;
	}
	return (token_len);
}

t_list	*parse_text(char **prompt, char **envp)
{
	int		token_len;
	char	*result;
	char	*temp;
	char	*quote;

	token_len = 0;
	quote = ft_strdup_gc("");
	token_len = get_token_len(prompt);
	if (token_len > 0)
	{
		result = ft_substr_gc(*prompt - token_len, 0, token_len);
		result = expand_str(result, envp);
		quote = ft_strjoin_gc(quote, result);
	}
	while (**prompt != '\0')
	{
		if ((**prompt == '"' || **prompt == '\''))
		{
			temp = parse_qoutes(prompt, **prompt, envp);
			quote = ft_strjoin_gc(quote, temp);
			continue ;
		}
		break ;
	}
	return (ft_lstnew_gc(token_init_gc(TEXT, quote)));
}

t_list	*parse_operator(char **prompt)
{
	char	symbol;
	char	*op;
	char	token_type;

	symbol = is_symbol(*prompt, 0);
	op = ft_char_to_str(symbol);
	if (!op)
		panic(NULL);
	if (ft_strchr("+#", symbol) != NULL)
		(*prompt)++;
	(*prompt)++;
	token_type = get_token_type(symbol);
	return (ft_lstnew_gc(token_init_gc(token_type, op)));
}

t_list	*parse_heredoc(char **prompt)
{
	int		token_len;
	char	*delimeter;
	char	*result;

	token_len = 0;
	(*prompt)++;
	(*prompt)++;
	skip_whitespace(prompt);
	while (**prompt != '\0')
	{
		if (ft_strchr("\t\n\v\f\r ", **prompt) != NULL)
			break ;
		token_len++;
		(*prompt)++;
	}
	delimeter = ft_substr_gc(*prompt - token_len, 0, token_len);
	result = open_heredoc_prompt(delimeter);
	return (ft_lstnew_gc(token_init_gc(HERE_DOC, result)));
}
