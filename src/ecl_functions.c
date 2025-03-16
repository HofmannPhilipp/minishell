/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecl_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:26:53 by cwolf             #+#    #+#             */
/*   Updated: 2025/03/16 14:48:10 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup_ecl(const char *s1)
{
	size_t	len;
	char	*dup;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	dup = (char *)ecl_alloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	ft_strlcpy(dup, s1, len + 1);
	return (dup);
}
