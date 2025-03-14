/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:58:00 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/13 13:46:48 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_atoi2(const char *str);

void	exec_exit(t_exec_cmd *cmd)
{
	unsigned char	code;
	
	ft_printf("exit\n");
	if (cmd->cmd_args[1] == NULL)
		exit(EXIT_SUCCESS);
	code = ft_atoi2(cmd->cmd_args[1]);
	if (cmd->cmd_args[2] != NULL)
	{
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
		code = 1;
	}
	exit(code);
}

static int	ft_iswhitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static int	ft_atoi2(const char *str)
{
	int		sign;
	int		sum;

	sign = 1;
	while (ft_iswhitespace(*str) && *str)
		str ++;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			sign = -1;
		str ++;
	}
	sum = 0;
	while (ft_isdigit(*str))
	{
		sum = sum * 10 + (*str - '0');
		str ++;
	}
	if (*str != '\0')
	{
		ft_putstr_fd("numeric argument required\n", STDERR_FILENO);
		return (255);
	}
	return (sign * sum);
}