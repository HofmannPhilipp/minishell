/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:00:37 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/16 14:46:49 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_plus(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		panic("fork fail");
	return (pid);
}

char	*ft_char_to_str(char c)
{
	char	*str;

	str = (char *)gc_alloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*get_env_var(char *key, char **envp)
{
	char	*value;

	value = get_envp(key, envp);
	if (!value)
		value = ft_strdup_gc("");
	else
		value = ft_strdup_gc(value);
	return (value);
}

void	reset_standard_fds(int in, int out, int err)
{
	if (dup2(in, STDIN_FILENO) > 0)
		panic("reset stdin fail");
	if (dup2(out, STDOUT_FILENO) > 0)
		panic("reset stdout fail");
	if (dup2(err, STDERR_FILENO) > 0)
		panic("reset stderr fail");
	close(in);
	close(out);
	close(err);
}

char	**copy_env(char *envp[])
{
	char	**copy;
	int		len;

	len = 0;
	while (envp[len] != NULL)
		len++;
	copy = (char **)ecl_alloc(sizeof(char *) * (len + 1));
	len = 0;
	while (envp[len] != NULL)
	{
		copy[len] = ft_strdup_ecl(envp[len]);
		len++;
	}
	copy[len] = NULL;
	return (copy);
}
