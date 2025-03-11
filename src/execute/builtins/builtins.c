/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:51:28 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/10 16:16:48 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_builtins(t_exec_cmd *cmd, char ***envp)
{
	char *builtin;
	int	len;

	builtin = cmd->cmd_args[0];
	len = ft_strlen(builtin);
	if (ft_strncmp(builtin, "cd", len) == 0)
		exec_cd(cmd);
	else if (ft_strncmp(builtin, "export", len) == 0)
		exec_export(cmd, envp);
	else if (ft_strncmp(builtin, "echo", len) == 0)
		exec_echo(cmd);
	else if (ft_strncmp(builtin, "unset", len) == 0)
		exec_unset(cmd, envp);

}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0)
		return (1);
	if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0)
		return (1);
	return (0);
}





