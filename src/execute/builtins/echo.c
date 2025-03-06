/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:15:13 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/06 12:18:39 by phhofman         ###   ########.fr       */
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

	while (args[i] && ft_strncmp(args[i], "-n", ft_strlen("-n")) == 0)
	{
		flag = 1;
		i++;
	}
	while (args[i])
	{
		if (args[i][0] != '\0')
		{
			ft_printf("%s", args[i]);

			int j = i + 1;
			while (args[j] && args[j][0] == '\0')
				j++;
			if (args[j])
				ft_printf(" ");
		}
		i++;
	}
	if (flag == 0)
		ft_printf("\n");
}