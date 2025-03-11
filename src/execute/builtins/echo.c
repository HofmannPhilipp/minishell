/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:15:13 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/11 12:14:38 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	exec_echo(t_exec_cmd *cmd)
{
	int		i;
	int		flag;
	char	**args;

	args = cmd->cmd_args;
	i = 1;
	flag = 0;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n' && args[i][2] == '\0')
	{
		flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (flag == 0)
		ft_printf("\n");
}
