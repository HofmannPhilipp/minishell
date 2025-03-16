/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:49:13 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/16 13:20:47 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run(t_cmd *cmd, char ***envp)
{
	int	*exit_status;

	if (!cmd)
		return ;
	if (cmd->type == BUILTIN)
	{
		run_builtins((t_exec_cmd *)cmd, envp);
		return ;
	}
	setup_signals(0);
	if (fork_plus() == 0)
		run_cmds(cmd, envp);
	exit_status = get_exit_status();
	wait(exit_status);
	if ((*exit_status & 0x7F) > 0)
		*exit_status = 128 + (*exit_status & 0x7F);
	else if ((*exit_status & 0x7F) == 0)
		*exit_status = (*exit_status >> 8) & 0xFF;
}

void	run_cmds(t_cmd *cmd, char ***envp)
{
	int	*exit_status;

	exit_status = get_exit_status();
	if (cmd->type == BUILTIN)
		run_builtins((t_exec_cmd *)cmd, envp);
	if (cmd->type == EXEC)
		run_exec((t_exec_cmd *)cmd, *envp);
	else if (cmd->type == PIPE)
		run_pipe((t_pipe_cmd *)cmd, *envp);
	else if (cmd->type == REDIR)
		run_redir((t_redir_cmd *)cmd, *envp);
	else if (cmd->type == HERE_DOC)
		run_heredoc((t_heredoc_cmd *)cmd, *envp);
	else if (cmd->type == SEQ)
		run_seq((t_seq_cmd *)cmd, *envp);
	else if (cmd->type == BACK)
		run_back((t_back_cmd *)cmd, *envp);
	gc_free_all();
	ecl_free_all();
	setup_signals(1);
	exit(*exit_status);
}

void	run_back(t_back_cmd *back, char *envp[])
{
	if (fork_plus() == 0)
		run_cmds(back->left, &envp);
	exit(EXIT_SUCCESS);
}

void	run_seq(t_seq_cmd *seq, char *envp[])
{
	int	*exit_status;

	if (fork_plus() == 0)
	{
		run_cmds((t_cmd *)seq->left, &envp);
		exit(EXIT_SUCCESS);
	}
	exit_status = get_exit_status();
	wait(exit_status);
	run((t_cmd *)seq->right, &envp);
}
