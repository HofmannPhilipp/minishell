/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:20:58 by cwolf             #+#    #+#             */
/*   Updated: 2025/03/16 16:14:01 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_redir(t_redir_cmd *redir, char *envp[])
{
	int	saved_in;
	int	saved_out;
	int	saved_err;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	saved_err = dup(STDERR_FILENO);
	close(redir->fd);
	if (open(redir->file, redir->mode, 0644) < 0)
	{
		gc_free_all();
		handle_error("No such file or directory\n", EXIT_FAILURE);
	}
	run_cmds(redir->cmd, &envp);
	reset_standard_fds(saved_in, saved_out, saved_err);
}

void	run_heredoc(t_heredoc_cmd *heredoc, char *envp[])
{
	int	tunnel[2];

	if (pipe(tunnel) == -1)
		handle_error("pipe failed\n", 1);
	write(tunnel[1], heredoc->value, ft_strlen(heredoc->value));
	close(tunnel[1]);
	dup2(tunnel[0], STDIN_FILENO);
	close(tunnel[0]);
	run_cmds(heredoc->cmd, &envp);
}
