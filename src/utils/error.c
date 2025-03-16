/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:46:28 by cwolf             #+#    #+#             */
/*   Updated: 2025/03/16 14:46:55 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	panic(char *error_msg)
{
	if (error_msg)
		ft_printf("%s", error_msg);
	exit(EXIT_FAILURE);
}

void	handle_error(char *msg, int exit_code)
{
	int	*exit_status;

	exit_status = get_exit_status();
	*exit_status = exit_code;
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	exit(exit_code);
}
