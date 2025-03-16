/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:45:50 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/16 14:41:07 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_cmd_args(t_list *list);

static void	process_tokens(t_list **list, char **cmd_args, t_cmd **cmd)
{
	t_token	*token;
	int		i;

	i = 0;
	while (*list)
	{
		token = (t_token *)(*list)->content;
		if (token->type == REDIR || token->type == HERE_DOC)
		{
			*cmd = parse_redir(list, *cmd);
			continue ;
		}
		if (token->type != TEXT)
			break ;
		cmd_args[i] = token->value;
		i++;
		*list = (*list)->next;
	}
}

t_cmd	*parse_exec(t_list **list)
{
	t_cmd		*cmd;
	t_exec_cmd	*exec;
	t_token		*token;
	char		**cmd_args;

	token = (t_token *)(*list)->content;
	if (token->type == PARENS)
		return (parse_block(list));
	cmd = exec_cmd_init(NULL);
	exec = (t_exec_cmd *)cmd;
	cmd = parse_redir(list, cmd);
	cmd_args = create_cmd_args(*list);
	process_tokens(list, cmd_args, &cmd);
	if (cmd_args[0] && is_builtin(cmd_args[0]) == 1)
		exec->type = BUILTIN;
	exec->cmd_args = cmd_args;
	return (cmd);
}

static char	**create_cmd_args(t_list *list)
{
	t_list	*head;
	t_token	*token;
	int		len;
	char	**cmd_args;

	head = list;
	len = 0;
	while (head)
	{
		token = (t_token *)(head)->content;
		if (token->type != TEXT)
			break ;
		head = head->next;
		len++;
	}
	cmd_args = (char **)gc_alloc(sizeof(char *) * (len + 1));
	cmd_args[len] = NULL;
	return (cmd_args);
}
