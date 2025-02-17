/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:05:48 by phhofman          #+#    #+#             */
/*   Updated: 2025/02/17 17:30:56 by phhofman         ###   ########.fr       */
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

int main(void)
{
	char	*input;
	// char	*res;
	t_list	*list;
	t_cmd	*cmd;
	while (1)
	{
		input = read_prompt();
		// char **split = ft_split2(input, "\t\n\v\f\r ");
		// print_string_array(split);
		list = convert_prompt_to_list(input);
		ft_lstiter(list, print_tokens);
		cmd = parse_cmd(&list);
		print_ast(cmd, 0);
		// append_node(&tokens, );
		// res = execute(input, envp);
		free(input);
		// ft_printf("%s\n", res);
		// free(res);
	}
	rl_clear_history();

	return (EXIT_SUCCESS);
}
