/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:22:50 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/16 00:08:31 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	display_env(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (env)
	{
		if (env->key && (env)->value[0])
			ft_printf("%s=%s\n", env->key, env->value);
		else if (env->key && env->equal);
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

// static void	set_path(t_data *data, t_env *env)

void		set_data(char **env, t_data *data)
{
	if (env && *env)
	{
		data->tenv = copy_tenv(env);
		// set_path(data, data->tenv);
	}
}