/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:05:48 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/07 15:19:07 by cwolf            ###   ########.fr       */
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
		// input = "echo \"hallo '$USER'\"";
		input = read_prompt();
		if (!input)
		{
			ft_printf("exit");
			exit(EXIT_SUCCESS);
		}
		list = tokenizer(input); //done
		if (list)
		{
			// ft_lstiter(list, print_tokens);
			cmd = parse_cmd(&list); //done
			// print_ast(cmd, 0);
			run(cmd, &envp);
		}
		gc_print_list();
		gc_free_all();
		gc_print_list();
		// free(input);
		check_check();
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
