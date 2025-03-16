/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:54:14 by cwolf             #+#    #+#             */
/*   Updated: 2025/03/16 14:56:43 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
