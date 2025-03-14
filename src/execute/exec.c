/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:52:06 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/14 18:05:23 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_exec(t_exec_cmd	*exec, char *envp[])
{
	char	*cmd_path;
	
	setup_signals(0);
	if (!exec->cmd_args[0])
		panic("no cmd args\n");
	if (access(exec->cmd_args[0], F_OK | X_OK) == 0)
		cmd_path = exec->cmd_args[0];
	else
		cmd_path = get_cmd_path(exec->cmd_args[0], envp);
	if (!cmd_path)
	{
		gc_free_all();
		handle_error("command not found\n", 127);
	}
	execve(cmd_path, exec->cmd_args, envp);
	panic("fail execve exec");
}

