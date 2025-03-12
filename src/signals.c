/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:23:23 by cwolf             #+#    #+#             */
/*   Updated: 2025/03/12 11:02:06 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sigint_handler(int sig)
{
    if ((sig == SIGINT) && g_pid != 0)
    {
        ft_putchar_fd('\n', 1);
    }
    else
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
    }
}

void setup_signals(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigint_handler);
    rl_catch_signals = 0;
}
