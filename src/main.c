/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:05:48 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/13 14:03:43 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_check()
{
    system("leaks minishell");
}


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
	
	(void)argc;
	(void)argv;
	envp = copy_env(envp);
	setup_signals(1);
	while (1)
	{
		// input = "echo <missing <\"./minishell_tester/test_files/infile\" <missing";
		input = read_prompt();
		if (!input)
		{
			ft_printf("exit\n");
			ecl_free_all();
			//ERROR CODE AENDERN VLLT 131
			exit(EXIT_SUCCESS);
		}
		list = tokenizer(input); 
		if (list)
		{
			// ft_lstiter(list, print_tokens);
			cmd = parse_cmd(&list); 
			// print_ast(cmd, 0);
			setup_signals(0);
			run(cmd, &envp);
		}
		setup_signals(1);
		// gc_print_list();
		gc_free_all();
		// gc_print_list();
		// free(input);
		// check_check();
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
