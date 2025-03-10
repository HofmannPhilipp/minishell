/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:39:35 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/10 13:38:33 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_env_var(char ***envp, char *key)
{
	char	**new_envp;
	int		i;
	int		len;
	int		j;
	
	if (get_envp(key, *envp) == NULL)
		return ;
	len = 0;
	while ((*envp)[len] != NULL)
		len++;
	new_envp = (char **)malloc(sizeof(char *) * len);
	new_envp[len] = NULL;
	i = 0;
	j = 0;
	while ((*envp)[i] != NULL)
	{
		if (ft_strncmp((*envp)[i], key, ft_strlen(key)) == 0)
		{
			i++;
			continue;
		}
		new_envp[j] = (*envp)[i];
		i++;
		j++;
	}
	free(*envp);
	*envp = new_envp;
}

void	exec_unset(t_exec_cmd *cmd, char ***envp)
{
	int	i;

	i = 1;
	if (cmd->cmd_args[i] == NULL)
		return ;
	
		while (cmd->cmd_args[i] != NULL)
		{
			del_env_var(envp, cmd->cmd_args[i]);
			i++;
		}
}