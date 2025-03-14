/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:49:05 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/14 12:13:19 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse_redir(t_list **list, t_cmd *cmd)
{
	t_token		*token;
	char		*redir_symbol;

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

	// Falls es sich um eine Eingabe-Redirection handelt ("<")
	if (ft_strncmp(redir_symbol, "<", 2) == 0)
	{
		// Falls `cmd` bereits eine Eingabe-Redirection ist, ersetze sie
		if (cmd->type == REDIR && ((t_redir_cmd *)cmd)->fd == STDIN_FILENO)
			((t_redir_cmd *)cmd)->file = token->value;
		else
		{
			// Erstelle eine neue Eingabe-Redirection
			cmd = redir_cmd_init(cmd, token->value, STDIN_FILENO, O_RDONLY);
		}
	}
	// Falls es sich um eine Ausgabe-Redirection handelt (">" oder ">>")
	else if (ft_strncmp(redir_symbol, ">", 2) == 0)
		cmd = redir_cmd_init(cmd, token->value, STDOUT_FILENO, O_WRONLY | O_CREAT | O_TRUNC);
	else if (ft_strncmp(redir_symbol, "+", 2) == 0)
		cmd = redir_cmd_init(cmd, token->value, STDOUT_FILENO, O_WRONLY | O_CREAT | O_APPEND);

	*list = (*list)->next;
	return (cmd);
}