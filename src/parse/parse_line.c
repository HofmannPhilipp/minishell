/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:51:12 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/12 16:28:26 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse_line(t_list **list)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = NULL;
	if (!*list)
		return (cmd);
	cmd = parse_pipe(list);
	if (!*list)
		return (cmd);
	token = (t_token *)(*list)->content;
	if (token->type == BACK)
	{
		*list = (*list)->next;
		cmd = back_cmd_init(cmd);
		if (*list)
			cmd = seq_cmd_init(cmd, parse_line(list));
	}
	else if (token->type == SEQ)
	{
		*list = (*list)->next;
		cmd = seq_cmd_init(cmd, parse_line(list));
	}
	return (cmd);
}
