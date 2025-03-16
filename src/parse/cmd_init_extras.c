/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init_extras.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:24:00 by cwolf             #+#    #+#             */
/*   Updated: 2025/03/16 13:25:01 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*seq_cmd_init(t_cmd *left, t_cmd *right)
{
	t_seq_cmd	*seq_cmd;

	seq_cmd = (t_seq_cmd *)gc_alloc(sizeof(t_seq_cmd));
	if (!seq_cmd)
		panic("malloc fail in seq init \n");
	seq_cmd->type = SEQ;
	seq_cmd->left = left;
	seq_cmd->right = right;
	return ((t_cmd *)seq_cmd);
}

t_cmd	*back_cmd_init(t_cmd *left)
{
	t_back_cmd	*back_cmd;

	back_cmd = (t_back_cmd *)gc_alloc(sizeof(t_back_cmd));
	if (!back_cmd)
		panic("malloc fail in back init \n");
	back_cmd->type = BACK;
	back_cmd->left = left;
	return ((t_cmd *)back_cmd);
}
