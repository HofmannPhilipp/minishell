/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:16:31 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/12 13:32:45 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cd(t_exec_cmd *cmd)
{
	char	*pwd;
	char	*new_pwd;
	int		ret;
	int		*exit_status;
	
	exit_status = get_exit_status();
	if (cmd->cmd_args[1] == NULL)
		ret = chdir(getenv("HOME"));
	else if (ft_strncmp(cmd->cmd_args[1], "..", 3) == 0)
	{
		pwd = getcwd(NULL, 0);
		new_pwd = ft_strrchr(pwd, '/');
		if (!new_pwd)
			return ;
		*new_pwd = '\0';
		ret = chdir(pwd);
	}
	else
		ret = chdir(cmd->cmd_args[1]);
	if (ret == -1)
	{
		ft_putstr_fd("No such file or directory", STDERR_FILENO);
		*exit_status = EXIT_FAILURE;
		return ;
	}
	*exit_status = EXIT_SUCCESS;
}
