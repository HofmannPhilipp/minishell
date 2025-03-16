/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:52:06 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/16 17:18:08 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_exec(t_exec_cmd	*exec, char *envp[])
{
	char	*cmd_path;

	setup_signals(0);
	if (!exec->cmd_args[0])
		handle_error(NULL, 0);
	if (access(exec->cmd_args[0], F_OK | X_OK) == 0)
		cmd_path = exec->cmd_args[0];
	else
		cmd_path = get_cmd_path(exec->cmd_args[0], envp);
	if (!cmd_path)
		handle_error("command not found\n", 127);
	execve(cmd_path, exec->cmd_args, envp);
	handle_error("execve failed\n", 1);
}
