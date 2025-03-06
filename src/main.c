/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:05:48 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/06 14:55:30 by phhofman         ###   ########.fr       */
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

int main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_list	*list;
	t_cmd	*cmd;
	
	(void)argc;
	(void)argv;
	envp = copy_env(envp);
	g_pid = 0;
	setup_signals();
	while (1)
	{
		// input = "echo \"hello world''\"\"\"myname is\"'robin'\"";
		input = read_prompt();
		if (!input)
		{
			ft_printf("exit");
			exit(EXIT_SUCCESS);
		}
		list = tokenizer(input);
		if (list)
		{
			ft_lstiter(list, print_tokens);
			cmd = parse_cmd(&list);
			print_ast(cmd, 0);
			run(cmd, &envp);
		}
		// free(input);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
