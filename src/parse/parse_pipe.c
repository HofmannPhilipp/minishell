/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:51:51 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/16 13:31:46 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse_pipe(t_list **list)
{
	t_token	*token;
	t_cmd	*cmd;

	cmd = NULL;
	if (!*list)
		return (cmd);
	cmd = parse_exec(list);
	if (!*list)
		return (cmd);
	token = (t_token *)(*list)->content;
	if (token->type == PIPE)
	{
		*list = (*list)->next;
		cmd = pipe_cmd_init(cmd, parse_pipe(list));
	}
	return (cmd);
}
