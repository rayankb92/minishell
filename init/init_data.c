/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:22:50 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/17 07:14:01 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	display_env(t_env *env)
{
	while (env)
	{
		if (env->key && (env)->value[0])
			ft_printf("%s=%s\n", env->key, env->value);
		else if (env->key && env->equal)
			ft_printf("%s=\n", env->key);
		env = env->next;
	}
}

char	*get_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

char	*get_value(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	return (ft_substr(str, i, ft_strlen(str)));
}

t_env	*copy_tenv(char **env)
{
	int		i;
	t_env	*new;

	i = 0;
	new = new_env(get_key(env[i]), get_value(env[i]), 1);
	while (env[++i])
	{
		add_back_env(&new, new_env(get_key(env[i]), get_value(env[i]), 1));
	}
	return (new);
}

static
void	tenv_to_env(t_data *data, char **env)
{
	int		i;

	data -> env = ft_calloc(sizeof(char *), ft_arraylen(env) + 1);
	i = -1;
	while (env[++i])
	{
		if (ft_strnstr(env[i], "PATH", 4))
			data -> path = ft_split(env[i] + 5, ':');
		data -> env[i] = ft_strdup(env[i]);
	}
}

int	init_data(t_data *data, char **env)
{
	ft_bzero(data, sizeof(t_data));
	data -> cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!data)
		return (EXIT_FAILURE);
	data -> prev_pipe = -1;
	data -> pipes[0] = -1;
	data -> pipes[1] = -1;
	if (env && *env)
	{
		data -> tenv = copy_tenv(env);
		tenv_to_env(data, env);
	}
	return (EXIT_SUCCESS);
}