/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:36:15 by phhofman          #+#    #+#             */
/*   Updated: 2025/02/12 13:44:49 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(char *error_msg, int exit_status)
{
	if (error_msg)
		ft_printf("%s\n", error_msg);
	else
		perror(NULL);
	exit(exit_status);
}

char	*get_envp(char *name, char *envp[])
{
	char	*sub;
	int		i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (envp[i] != NULL)
	{
		sub = ft_substr(envp[i], 0, len);
		if (!sub)
			return (NULL);
		if (ft_strncmp(name, sub, len) == 0)
		{
			free(sub);
			return (envp[i] + len + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char *envp[])
{
	char	**paths;
	char	*path;
	int		i;
	char	*cmd_temp;

	cmd_temp = ft_strjoin("/", cmd);
	if (!cmd_temp)
		return (NULL);
	paths = get_paths(envp);
	i = 0;
	while (paths[i] != NULL)
	{
		path = ft_strjoin(paths[i], cmd_temp);
		if (!path)
			return (free(cmd_temp), free_str_arr(paths), NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (free(cmd_temp), free_str_arr(paths), path);
		free(path);
		i++;
	}
	return (free(cmd_temp), free_str_arr(paths), NULL);
}

char	**get_paths(char *envp[])
{
	char	*env;
	char	**paths;

	env = get_envp("PATH", envp);
	if (!envp)
	{
		ft_printf("No path found");
		return (NULL);
	}
	paths = ft_split(env, ':');
	if (!paths)
		return (NULL);
	return (paths);
}