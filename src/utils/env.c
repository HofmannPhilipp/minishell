/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:36:15 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/16 16:51:47 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_envp(char *key, char *envp[])
{
	char	*sub;
	int		i;
	size_t	len;

	len = ft_strlen(key);
	i = 0;
	while (envp[i] != NULL)
	{
		sub = ft_substr_gc(envp[i], 0, len);
		if (!sub)
			return (NULL);
		if (ft_strncmp(key, sub, len) == 0)
		{
			gc_free_one(sub);
			return (envp[i] + len + 1);
		}
		gc_free_one(sub);
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
	if (paths == NULL)
		return (free(cmd_temp), NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		path = ft_strjoin_gc(paths[i], cmd_temp);
		if (!path)
			return (free(cmd_temp), free_str_arr(paths), NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (free(cmd_temp), free_str_arr(paths), path);
		gc_free_one(path);
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
