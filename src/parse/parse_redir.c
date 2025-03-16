/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:49:05 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/16 13:50:17 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*handle_redirection(t_cmd *cmd, char *redir_symbol, char *file_value)
{
	if (ft_strncmp(redir_symbol, "<", 2) == 0)
	{
		if (cmd->type == REDIR && ((t_redir_cmd *)cmd)->fd == STDIN_FILENO)
			((t_redir_cmd *)cmd)->file = file_value;
		else
			cmd = redir_cmd_init(cmd, file_value, STDIN_FILENO, O_RDONLY);
	}
	else if (ft_strncmp(redir_symbol, ">", 2) == 0)
	{
		cmd = redir_cmd_init(cmd, file_value, STDOUT_FILENO,
				O_WRONLY | O_CREAT | O_TRUNC);
	}
	else if (ft_strncmp(redir_symbol, "+", 2) == 0)
	{
		cmd = redir_cmd_init(cmd, file_value, STDOUT_FILENO,
				O_WRONLY | O_CREAT | O_APPEND);
	}
	return (cmd);
}

t_cmd	*parse_redir(t_list **list, t_cmd *cmd)
{
	t_token	*token;
	char	*redir_symbol;

	if (!*list)
		return (cmd);
	token = (t_token *)(*list)->content;
	if (token->type != REDIR && token->type != HERE_DOC)
		return (cmd);
	if (token->type == HERE_DOC)
	{
		cmd = heredoc_cmd_init(cmd, token->value);
		*list = (*list)->next;
		return (cmd);
	}
	redir_symbol = token->value;
	*list = (*list)->next;
	token = (t_token *)(*list)->content;
	if (token->type != TEXT)
		panic("error redirect fail no file");
	cmd = handle_redirection(cmd, redir_symbol, token->value);
	*list = (*list)->next;
	return (cmd);
}
