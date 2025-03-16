/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:10:29 by cwolf             #+#    #+#             */
/*   Updated: 2025/03/16 16:13:29 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_pipe(t_pipe_cmd *pipe_cmd, char *envp[])
{
	int	tunnel[2];
	int	*exit_status;

	if (pipe(tunnel) < 0)
		handle_error("pipe failed\n", 1);
	if (fork_plus() == 0)
	{
		close(tunnel[0]);
		dup2(tunnel[1], STDOUT_FILENO);
		close(tunnel[1]);
		run_cmds(pipe_cmd->left, &envp);
	}
	if (fork_plus() == 0)
	{
		close(tunnel[1]);
		dup2(tunnel[0], STDIN_FILENO);
		close(tunnel[0]);
		run_cmds(pipe_cmd->right, &envp);
	}
	close(tunnel[0]);
	close(tunnel[1]);
	exit_status = get_exit_status();
	wait(NULL);
	wait(exit_status);
	update_exit_status(exit_status);
}
