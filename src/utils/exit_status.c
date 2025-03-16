/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:07:09 by cwolf             #+#    #+#             */
/*   Updated: 2025/03/16 17:44:56 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*get_exit_status(void)
{
	static int	exit_status = 0;

	return (&exit_status);
}

void	update_exit_status(int *exit_status)
{
	if ((*exit_status & 0x7F) > 0)
		*exit_status = 128 + (*exit_status & 0x7F);
	else if ((*exit_status & 0x7F) == 0)
		*exit_status = (*exit_status >> 8) & 0xFF;
}
