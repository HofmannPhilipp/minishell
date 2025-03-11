/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:49:13 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/11 12:23:44 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    run(t_cmd *cmd, char ***envp)
{
    if (!cmd)
    	return ;
    if (cmd->type == BUILTIN)
    {
        run_builtins((t_exec_cmd *)cmd, envp);
        return ;
    }
    if (fork_plus() == 0)
        run_cmds(cmd, envp);
    wait(NULL);
    g_pid = 0;
}
void    run_cmds(t_cmd *cmd, char ***envp) //done
{
	int	*exit_status;
	
	if (!cmd)
	return ;
	if (cmd->type == BUILTIN)
	{
		run_builtins((t_exec_cmd *)cmd, envp);
		return ;
	}
	if (fork_plus() == 0)
		run_cmds(cmd, envp);
	exit_status = get_exit_status();
	wait(exit_status);
	g_pid = 0;
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
	exit(EXIT_FAILURE);
}

void	run_pipe(t_pipe_cmd *pipe_cmd, char *envp[])
{
	int	tunnel[2];
	int pid1;
	int	pid2;
	int	*exit_status;
	
	if (pipe(tunnel) < 0)
	panic("pipe fail");
	pid1 = fork_plus();
	if (pid1 == 0)
	{
		close(tunnel[0]);
		dup2(tunnel[1], STDOUT_FILENO);
		close(tunnel[1]);
		run_cmds(pipe_cmd->left, &envp);
	}
	pid2 = fork_plus();
	if (pid2 == 0)
	{
		close(tunnel[1]);
		dup2(tunnel[0], STDIN_FILENO);
		close(tunnel[0]);
		run_cmds(pipe_cmd->right, &envp);
	}
	exit_status = get_exit_status();
	close(tunnel[0]);
	close(tunnel[1]);
	waitpid(pid1, exit_status, 0);
	waitpid(pid2, exit_status, 0);
}

void	run_back(t_back_cmd *back, char *envp[])
{
    if (fork_plus() == 0)
		run(back->left, &envp);
    exit(EXIT_SUCCESS);
}
void    run_seq(t_seq_cmd *seq, char *envp[])
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
void    run_redir(t_redir_cmd *redir, char *envp[]) //done
{
	int	saved_in;
	int	saved_out;
	int	saved_err;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	saved_err = dup(STDERR_FILENO);
	close(redir->fd);
	if (open(redir->file, redir->mode, 0644) < 0)
		panic("redir open failed");
	run_cmds(redir->cmd, &envp);
	reset_standard_fds(saved_in, saved_out, saved_err);
}
void    run_heredoc(t_heredoc_cmd *heredoc, char *envp[])
{
		int tunnel[2];

	if (pipe(tunnel) == -1)
		panic("pipe failed");

	write(tunnel[1], heredoc->value, ft_strlen(heredoc->value));
	close(tunnel[1]);
	dup2(tunnel[0], STDIN_FILENO);
	close(tunnel[0]);
	run_cmds(heredoc->cmd, &envp);
}

