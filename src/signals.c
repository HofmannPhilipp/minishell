/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:23:23 by cwolf             #+#    #+#             */
/*   Updated: 2025/03/13 14:07:25 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void parent_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		(void)sig;
	}
	return ;
}

static void child_handler(int sig)
{
	int *exit_status;
	
	exit_status = get_exit_status();
	write(1, "c", 1);
	if (sig == SIGINT)
	{
		(void)sig;
		*exit_status = 130;
	}
	else if (sig == SIGQUIT)
	{
		(void)sig;
		*exit_status = 131;
	}
	return ;
}

void setup_signals(int in_child)
{
	struct sigaction sa;
	
	sigemptyset(&sa.sa_mask);
	if (in_child)
		sa.sa_handler = &parent_handler;
	else
		sa.sa_handler = &child_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	rl_catch_signals = 0;
}
