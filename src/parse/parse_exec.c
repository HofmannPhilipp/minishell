/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:45:50 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/13 15:34:00 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_cmd_args(t_list *list);

t_cmd	*parse_exec(t_list **list)
{
	t_cmd		*cmd;
	t_exec_cmd	*exec;
	t_token		*token;
	char		**cmd_args;
	int			i;

	token = (t_token *)(*list)->content;
	if (token->type == PARENS)
		return (parse_block(list)); 
	cmd = exec_cmd_init(NULL);
	exec = (t_exec_cmd *)cmd;
	cmd_args = create_cmd_args(*list); // Speicher reservieren
	i = 0;

	while (*list)
	{
		token = (t_token *)(*list)->content;

		// Falls es eine Redirection ist, parse sie sofort
		if (token->type == REDIR || token->type == HERE_DOC)
		{
			cmd = parse_redir(list, cmd);
			continue;
		}

		// Falls kein TEXT-Token mehr da ist, abbrechen
		if (token->type != TEXT)
			break;

		// Argument zum cmd_args hinzufügen
		cmd_args[i] = token->value;
		i++;
		*list = (*list)->next;
	}

	// Falls es ein Builtin ist, setze den Typ
	if (cmd_args[0] && is_builtin(cmd_args[0]) == 1)
		exec->type = BUILTIN;

	exec->cmd_args = cmd_args; // ["cat", "Makefile"]
	return (cmd);
}

static char	**create_cmd_args(t_list *list)
{
	t_list		*head;
	t_token		*token;
	int			len;
	char		**cmd_args;
	
	head = list;
	len = 0;
	while (head)
	{
		token = (t_token *)(head)->content;
		if (token->type != TEXT)
			break;
		head = head->next;
		len ++;
	}
	cmd_args = (char **)gc_alloc(sizeof(char *) * (len + 1));
	cmd_args[len] = NULL;
	return (cmd_args);
}

