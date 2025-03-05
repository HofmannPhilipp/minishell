/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:51:28 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/05 10:12:55 by phhofman         ###   ########.fr       */
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

static	int		nb_args(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

void	exec_echo(t_exec_cmd *cmd)
{
	{
		int		i;
		int		n_option;
		char	**args;

		args = cmd->cmd_args;
		i = 1;
		n_option = 0;
		if (nb_args(args) > 1)
		{
			while (args[i] && ft_strncmp(args[i], "-n", ft_strlen("-n")) == 0)
			{
				n_option = 1;
				i++;
			}
			while (args[i])
			{
				ft_putstr_fd(args[i], 1);
				if (args[i + 1] && args[i][0] != '\0' && !ft_strchr("'\"", args[i][0]) && !ft_strchr("'\"", args[i + 1][0]))
					write(1, " ", 1);
				i++;
			}
		}
		if (n_option == 0)
			write(1, "\n", 1);
	}
}

void	exec_cd(t_exec_cmd *cmd)
{
	char	*pwd;
	char	*new_pwd;

	if (ft_strncmp(cmd->cmd_args[0], "cd", 3) != 0)
		return ;
	if (cmd->cmd_args[1] == NULL)
		chdir(getenv("HOME"));
	else if (ft_strncmp(cmd->cmd_args[1], "..", 3) == 0)
	{
		pwd = getcwd(NULL, 0);
		new_pwd = ft_strrchr(pwd, '/');
		if (!new_pwd)
			return ;
		*new_pwd = '\0';
		chdir(pwd);
	}
	else
		chdir(cmd->cmd_args[1]);
}

void	exec_export(t_exec_cmd *cmd, char ***envp)
{
	int	i;

	i = 1;
	if (cmd->cmd_args[i] == NULL)
	{
		print_export(*envp);
		return ;
	}
	while (cmd->cmd_args[i] != NULL)
	{
		add_env_var(envp, cmd->cmd_args[i]);
		i++;
	}
}

