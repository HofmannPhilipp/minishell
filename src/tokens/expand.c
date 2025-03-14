/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:43:47 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/14 16:12:23 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_env_name(char *str, int *i)
{
	int		start;
	char	*env_name;

	start = (*i);
	while (str[*i] && !ft_strchr("\t\n\v\f\r '\"();|&<>$", str[*i]))
		(*i)++;
	env_name = ft_substr_gc(str, start, *i - start);
	if (!env_name)
		panic("malloc fail");
	return (env_name);
}
static char	*replace_env_variable(char *str, int *i, char *result, char **envp)
{
	char	*temp;
	char	*env_name;
	char	*env_value;
	int		*exit_status;
	
	if (ft_strchr("\t\n\v\f\r ", str[*i + 1]) || str[*i + 1] == '\0')
	{
		temp = result;
		result = ft_strjoin_gc(temp, "$");
		// free(temp);
		(*i)++;
		return (result);
	}
	(*i)++;
	env_name = extract_env_name(str, i);
	if(ft_strncmp(env_name, "?", ft_strlen("?")) == 0)
	{
		exit_status = get_exit_status();
		env_value = ft_itoa_gc(*exit_status);
	}
	else
		env_value = get_env_var(env_name, envp);
	temp = result;
	result = ft_strjoin_gc(temp, env_value);
	return (result);
}

static char	*append_normal_text(char *str, int *i, char *result)
{
	int		start;
	char	*temp;
	char	*text_part;

	start = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	text_part = ft_substr_gc(str, start, *i - start);
	if (!text_part)
		panic ("malloc fail");
	temp = result;
	result = ft_strjoin_gc(temp, text_part);
	gc_free_one(text_part);
	// if (!result)
	// 	panic("malloc fail");
	return (result);
}

char	*expand_str(char *str, char **envp)
{
	char	*result;
	int		i;

	result = ft_strdup_gc("");
	if (!result)
		panic("malloc fail");

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			result = replace_env_variable(str, &i, result, envp);
		else
			result = append_normal_text(str, &i, result);
	}
	return (result);
}

