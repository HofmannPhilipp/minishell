/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:05:48 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/14 15:01:22 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_prompt()
{
	char	*prompt;
	char	*input;
	
	prompt = "🤏🐚\033[0;32m $ \033[0m";

	input = readline(prompt);
	add_history(input);
	return (input);
}

int	*get_exit_status(void)
{
	static int	exit_status = 0;
	return (&exit_status);
}

int main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_list	*list;
	t_cmd	*cmd;
	int		*exit_status;
	
	(void)argc;
	(void)argv;
	envp = copy_env(envp);
	setup_signals(1);
	exit_status = get_exit_status();
	while (1)
	{
		input = read_prompt();
		if (!input)
		{
			ft_printf("exit\n");
			ecl_free_all();
			exit(*exit_status);
		}
		list = tokenizer(input); 
		if (list)
		{
			cmd = parse_cmd(&list); 
			setup_signals(0);
			run(cmd, &envp);
		}
		setup_signals(1);
		gc_free_all();
		free(input);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
