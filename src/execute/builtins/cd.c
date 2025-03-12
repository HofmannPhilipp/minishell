/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:16:31 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/12 13:16:27 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cd(t_exec_cmd *cmd)
{
	char	*pwd;
	char	*new_pwd;

	if (ft_strncmp(cmd->cmd_args[0], "cd", 3) != 0)
		return ;
	if (cmd->cmd_args[1] == NULL)
		chdir(getenv("HOME"));
	else if (ft_strncmp(cmd->cmd_args[1], "..", 3) == 0)
	{
		pwd = getcwd(NULL, 0);
		new_pwd = ft_strrchr(pwd, '/');
		if (!new_pwd)
			return ;
		*new_pwd = '\0';
		chdir(pwd);
		free(pwd);
	}
	else
		chdir(cmd->cmd_args[1]);
}
