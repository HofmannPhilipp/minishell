/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:37:42 by cwolf             #+#    #+#             */
/*   Updated: 2025/03/11 15:44:29 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr_gc(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	size_t			sublen;

	if (!s)
		return (NULL);
	sublen = ft_strlen(s);
	if (len > sublen - start)
		len = sublen - start;
	if (sublen <= start)
	{
		sub = (char *)gc_alloc(sizeof(char) * 1);
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	sub = (char *)gc_alloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
char	*ft_strjoin_gc(char const *s1, char const *s2)
{
	size_t	joinlen;
	char	*join;

	joinlen = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)gc_alloc(sizeof(char) * (joinlen + 1));
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, joinlen + 1);
	ft_strlcat(join, s2, joinlen + 1);
	return (join);
}

char	*ft_strdup_gc(const char *s1)
{
	size_t	len;
	char	*dup;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	dup = (char *)gc_alloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	ft_strlcpy(dup, s1, len + 1);
	return (dup);
}

t_list	*ft_lstnew_gc(void *content)
{
	t_list	*node;

	node = (t_list *)gc_alloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

t_token	*token_init_gc(int type, char *value)
{
	t_token	*token;

	token = (t_token *)gc_alloc(sizeof(t_token));
	if (!token)
		panic("malloc fail in token init");
	token->type = type;
	token->value = value;
	return (token);
}

//split_gc 

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

//itoa
static size_t	get_digit_count(int n)
{
	size_t	len;

	len = 0;
	while (n > 0)
	{
		n = n / 10;
		len ++;
	}
	return (len);
}

static void	convert_number_to_string(char *str, int n, size_t i)
{
	while (n > 0)
	{
		str[i] = (n % 10) + '0';
		n = n / 10;
		i --;
	}
}
char	*ft_itoa_gc(int n)
{
	char	*result_str;
	size_t	len;
	int		is_negative;

	is_negative = 0;
	if (n <= 0)
	{
		if (n == -2147483648)
			return (ft_strdup("-2147483648"));
		if (n == 0)
			return (ft_strdup("0"));
		n = -n;
		is_negative = 1;
	}
	len = get_digit_count(n) + is_negative;
	result_str = (char *)gc_alloc(sizeof(char) * (len + 1));
	if (!result_str)
		return (NULL);
	result_str[len] = '\0';
	convert_number_to_string(result_str, n, len - 1);
	if (is_negative)
		result_str[0] = '-';
	return (result_str);
}