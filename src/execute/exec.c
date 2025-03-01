/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:52:06 by phhofman          #+#    #+#             */
/*   Updated: 2025/02/28 23:19:15 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_exec(t_exec_cmd	*exec, char *envp[])
{
	char	*cmd_path;

	if (!exec->cmd_args[0])
		panic("no cmd_args");
	if (access(exec->cmd_args[0], F_OK | X_OK) == 0)
		cmd_path = exec->cmd_args[0];
	else
		cmd_path = get_cmd_path(exec->cmd_args[0], envp);
	if (!cmd_path)
	{
		// free cmd_args and t_cmd exec
		panic("find cmd_path fail");
	}
	execve(cmd_path, exec->cmd_args, envp);
	panic("fail execve exec");
}

