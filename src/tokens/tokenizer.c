/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:10:07 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/07 15:51:10 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	is_symbol(char *str, int in_quotes)
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

static void	skip_whitespace(char **prompt)
{
	while (ft_strchr("\t\n\v\f\r ", **prompt) != NULL && **prompt != '\0')
			(*prompt) ++;
}

static	char	*parse_qoutes(char **prompt, char quote_type)
{
	int		token_len;
	char	*result;
	char c;
	char *str;
	token_len = 0;
	(*prompt)++;
	c = **prompt;
	while (**prompt != '\0' && **prompt != quote_type)
	{
		c = **prompt;
		str = *prompt;
		token_len++;
		(*prompt)++;
	}
	if (token_len == 0)
	{
		(*prompt)++;
		return (ft_strdup(""));
	}
	c = **prompt;
	str = *prompt;
	result = ft_substr(*prompt - token_len, 0, token_len);
	if (**prompt != quote_type)
		result = open_quote_prompt(result, quote_type);
	if (quote_type == '"')
		result = expand_str(result);
	(*prompt)++;
	return (result);
}
static t_list *parse_text(char **prompt)
{
	int		token_len;
	char	quote_type;
	char	*result;
	char	*str;
	char	*temp;
	char	*quote;
	token_len = 0;
	quote_type = 0;

	char c;
	quote = ft_strdup("");
	while (**prompt != '\0')
	{
		c = **prompt;
		str = *prompt;
		if((**prompt == '"' || **prompt == '\''))
		{
			if (token_len > 0)
			{
				result = ft_substr(*prompt - token_len, 0, token_len);
				quote = ft_strjoin(quote, result);
			}
			temp = parse_qoutes(prompt, **prompt);
			str = *prompt;
			c = **prompt;
			quote = ft_strjoin(quote, temp);
			token_len = 0;
			continue;
		}
		if ((ft_strchr("\t\n\v\f\r ", **prompt) || is_symbol(*prompt, 0) != 'a'))
			break;
		(*prompt)++;
		token_len++;
	}
	str = *prompt;
	c = **prompt;
	result = ft_substr(*prompt - token_len, 0, token_len);
	result = expand_str(result);
	if (quote != NULL)
		result = ft_strjoin(quote, result);
	return (ft_lstnew(token_init(TEXT, result)));
}

static t_list *parse_operator(char **prompt)
{
	char	symbol;
	char	*op;
	char	token_type;

	symbol = is_symbol(*prompt, 0);
	op = ft_char_to_str(symbol);
	if (!op)
		panic(NULL);
	if (ft_strchr("+#", symbol) != NULL)
		(*prompt) ++;
	(*prompt) ++;
	token_type = get_token_type(symbol);
	return (ft_lstnew(token_init(token_type, op)));
}

static t_list *parse_heredoc(char **prompt)
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
			break;
		token_len++;
		(*prompt)++;
	}
		delimeter = ft_substr(*prompt - token_len, 0, token_len);
		result = open_heredoc_prompt(delimeter);
		free(delimeter);
	return(ft_lstnew(token_init(HERE_DOC, result)));
}

t_list	*tokenizer(char *prompt)
{
	t_list	*tokens;
	t_list	*node;

	if (!prompt)
		return (NULL);
	tokens = NULL;
	while (*prompt != '\0')
	{
		skip_whitespace (&prompt);
		if (*prompt == '\0')
			break;
		if (is_symbol(prompt, 0) == '#')
			node = parse_heredoc(&prompt);
		else if (is_symbol(prompt, 0) == 'a')
			node = parse_text(&prompt);
		else
			node = parse_operator(&prompt);
		ft_lstadd_back(&tokens, node);
	}
	return (tokens);
}

int	get_token_type(char	c)
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
