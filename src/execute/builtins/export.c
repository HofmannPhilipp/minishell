/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:40:51 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/14 12:18:32 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(const char *str)
{
	int i;

	if (!str || str[0] == '\0')
		return (0);
	
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	
	i = 1;
	while(str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	replace_env_entry(char ***envp, char *key, char *entry)
{
	int	i;

	i = 0;
	while((*envp)[i] != NULL)
	{
		if (ft_strncmp((*envp)[i], key, ft_strlen(key)) == 0)
		{
			free((*envp)[i]);
			(*envp)[i] = entry;
			return ;
		}
		i++;
	}
}

void	add_env_var(char ***envp, char *entry)
{
	char	**new_envp;
	char	*value;
	int		i;
	char	*key;
	int		*exit_status;
	
	exit_status = get_exit_status();
	key = ft_strdup_gc(entry);
	entry = ft_strdup_ecl(entry);
	value = ft_strchr(key, '=');
	if (value)
		*value = '\0';
	if (is_valid_identifier(key) == 0)
	{
		ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
		*exit_status = EXIT_FAILURE;
		return ;
	}
	if (get_envp(key, *envp) != NULL)
	{
		replace_env_entry(envp, key, entry);
		return ;
	}
	i = 0;
	while ((*envp)[i] != NULL)
		i++;
	new_envp = (char **)ecl_alloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*envp)[i] != NULL)
	{
		new_envp[i] = (*envp)[i];
		i++;
	}
	new_envp[i] = entry;
	new_envp[i + 1] = NULL;
	// free(*envp);
	*envp = new_envp;
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
