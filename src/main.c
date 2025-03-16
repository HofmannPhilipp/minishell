/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:05:48 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/16 15:06:37 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_prompt(void)
{
	char	*prompt;
	char	*input;

	prompt = "🤏🐚\033[0;32m $ \033[0m";
	input = readline(prompt);
	add_history(input);
	return (input);
}

static void	process_loop(char *envp[], int *exit_status)
{
	char	*input;
	t_list	*list;
	t_cmd	*cmd;

	while (1)
	{
		input = read_prompt();
		if (!input)
		{
			ft_printf("exit\n");
			ecl_free_all();
			exit(*exit_status);
		}
		list = tokenizer(input, envp);
		if (list)
		{
			ft_list_remove(&list);
			cmd = parse_cmd(&list);
			setup_signals(0);
			run(cmd, &envp);
		}
		setup_signals(1);
		gc_free_all();
		free(input);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int		*exit_status;

	(void)argc;
	(void)argv;
	envp = copy_env(envp);
	setup_signals(1);
	exit_status = get_exit_status();
	process_loop(envp, exit_status);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
