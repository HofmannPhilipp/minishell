/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_functions_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:52:00 by cwolf             #+#    #+#             */
/*   Updated: 2025/03/16 14:52:29 by cwolf            ###   ########.fr       */
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
