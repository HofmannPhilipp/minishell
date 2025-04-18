/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:05:51 by phhofman          #+#    #+#             */
/*   Updated: 2024/10/15 13:02:58 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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

char	*ft_itoa(int n)
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
	result_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!result_str)
		return (NULL);
	result_str[len] = '\0';
	convert_number_to_string(result_str, n, len - 1);
	if (is_negative)
		result_str[0] = '-';
	return (result_str);
}
