/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:49:05 by phhofman          #+#    #+#             */
/*   Updated: 2025/02/18 09:47:22 by phhofman         ###   ########.fr       */
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
	if (token->type != REDIR)
		return (cmd);
	redir_symbol = token->value;
	*list = (*list)->next;
	token = (t_token *)(*list)->content;
	if (token->type != TEXT)
		panic("error redirect fail no file");
	if (ft_strncmp(redir_symbol, "<", 2) == 0)
		cmd = redir_cmd_init(cmd, token->value, STDIN_FILENO, O_RDONLY);
	if (ft_strncmp(redir_symbol, ">", 2) == 0)
		cmd = redir_cmd_init(cmd, token->value, STDOUT_FILENO, O_WRONLY | O_CREAT | O_TRUNC);
	if (ft_strncmp(redir_symbol, "+", 2) == 0)
		cmd = redir_cmd_init(cmd, token->value, STDOUT_FILENO, O_WRONLY | O_CREAT);
	*list = (*list)->next;
	return (cmd);
}
