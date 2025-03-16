/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:16:31 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/16 16:25:46 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_cd_exit_status(int ret, int *exit_status)
{
	if (ret == -1)
	{
		ft_putstr_fd("No such file or directory", STDERR_FILENO);
		*exit_status = EXIT_FAILURE;
	}
	else
		*exit_status = EXIT_SUCCESS;
}

void	exec_cd(t_exec_cmd *cmd)
{
	char	*pwd;
	char	*new_pwd;
	int		ret;
	int		*exit_status;

	exit_status = get_exit_status();
	if (cmd->cmd_args[1] == NULL || ft_strncmp(cmd->cmd_args[1], "~", 2) == 0)
		ret = chdir(getenv("HOME"));
	else if (ft_strncmp(cmd->cmd_args[1], "..", 3) == 0)
	{
		pwd = getcwd(NULL, 0);
		new_pwd = ft_strrchr(pwd, '/');
		if (!new_pwd)
			return ;
		*new_pwd = '\0';
		if (ft_strlen(pwd) == 0)
			ret = chdir("/");
		else
			ret = chdir(pwd);
		free(pwd);
	}
	else
		ret = chdir(cmd->cmd_args[1]);
	set_cd_exit_status(ret, exit_status);
}
