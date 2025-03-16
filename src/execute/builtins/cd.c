/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:16:31 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/16 12:52:20 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_directory(char *path, int *exit_status)
{
	int	ret;

	ret = chdir(path);
	if (ret == -1)
	{
		ft_putstr_fd("No such file or directory", STDERR_FILENO);
		*exit_status = EXIT_FAILURE;
	}
	else
	{
		*exit_status = EXIT_SUCCESS;
	}
}

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
		if (ft_strlen(pwd) == 0)
			ret = chdir("/");
		else
			ret = chdir(pwd);
		free(pwd);
	}
	else
		change_directory(cmd->cmd_args[1], exit_status);
}
