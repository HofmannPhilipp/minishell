/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:57:25 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/16 13:24:30 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*exec_cmd_init(char **cmd_args)
{
	t_exec_cmd	*exec_cmd;

	exec_cmd = (t_exec_cmd *)gc_alloc(sizeof(t_exec_cmd));
	if (!exec_cmd)
		panic("malloc fail in exec init \n");
	exec_cmd->type = EXEC;
	exec_cmd->cmd_args = cmd_args;
	return ((t_cmd *)exec_cmd);
}

t_cmd	*redir_cmd_init(t_cmd *cmd, char *file, int fd, int mode)
{
	t_redir_cmd	*redir_cmd;

	redir_cmd = (t_redir_cmd *)gc_alloc(sizeof(t_redir_cmd));
	if (!redir_cmd)
		panic("malloc fail in redir init \n");
	redir_cmd->type = REDIR;
	redir_cmd->cmd = cmd;
	redir_cmd->file = file;
	redir_cmd->fd = fd;
	redir_cmd->mode = mode;
	return ((t_cmd *)redir_cmd);
}

t_cmd	*heredoc_cmd_init(t_cmd *cmd, char *value)
{
	t_heredoc_cmd	*heredoc_cmd;

	heredoc_cmd = (t_heredoc_cmd *)gc_alloc(sizeof(t_heredoc_cmd));
	heredoc_cmd->type = HERE_DOC;
	heredoc_cmd->cmd = cmd;
	heredoc_cmd->value = value;
	return ((t_cmd *)heredoc_cmd);
}

t_cmd	*pipe_cmd_init(t_cmd *left, t_cmd *right)
{
	t_pipe_cmd	*pipe_cmd;

	pipe_cmd = (t_pipe_cmd *)gc_alloc(sizeof(t_pipe_cmd));
	if (!pipe_cmd)
		panic("malloc fail in pipe init \n");
	pipe_cmd->type = PIPE;
	pipe_cmd->left = left;
	pipe_cmd->right = right;
	return ((t_cmd *)pipe_cmd);
}
