/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:37:42 by cwolf             #+#    #+#             */
/*   Updated: 2025/03/16 14:56:46 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_memory(char **tokens, int i)
{
	while (i >= 0)
	{
		gc_free_one(tokens[i]);
		i --;
	}
	gc_free_one(tokens);
}

static size_t	count_tokens(char const *s, char c)
{
	size_t	token_count;
	int		i;
	int		inside_token;

	token_count = 0;
	i = 0;
	while (s[i])
	{
		inside_token = 0;
		while (s[i] != c && s[i] != '\0')
		{
			inside_token = 1;
			i++;
		}
		if (inside_token)
			token_count++;
		if (s[i] != '\0')
			i++;
	}
	return (token_count);
}

static int	fill_tokens(char **tokens, char const *s, char c)
{
	int		token_len;
	int		token_index;
	char	*token;

	token_index = 0;
	while (*s)
	{
		while (*s == c && *s)
			s ++;
		token_len = 0;
		while (s[token_len] != c && s[token_len] != '\0')
			token_len ++;
		if (token_len > 0)
		{
			token = ft_substr_gc(s, 0, token_len);
			if (!token)
			{
				free_memory(tokens, token_index - 1);
				return (0);
			}
			tokens[token_index ++] = token;
			s += token_len;
		}
	}
	return (1);
}

char	**ft_split_gc(char const *s, char c)
{
	size_t	token_count;
	char	**tokens;

	if (!s)
		return (NULL);
	token_count = count_tokens(s, c);
	tokens = (char **)gc_alloc(sizeof(char *) * (token_count + 1));
	if (!tokens)
		return (NULL);
	tokens[token_count] = NULL;
	if (!fill_tokens(tokens, s, c))
		return (NULL);
	return (tokens);
}
