/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:22:50 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/11 23:28:34 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*copy_env(char **env)
{
	int		i;
	t_list	*new;

	i = 0;
	new = ft_lstnew(ft_strdup(env[i]));
	while (env[++i])
		ft_lstadd_back(&new, ft_lstnew(ft_strdup(env[i])));
	return (new);
}

void	display_env(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (env)
	{
		if (env->key && env->value)
			ft_printf("%s='%s'\n", env->key, env->value);
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
	new = new_env(get_key(env[i]), get_value(env[i]));
	while (env[++i])
	{
		add_back_env(&new, new_env(get_key(env[i]), get_value(env[i])));
	}
	return (new);
}

void		set_data(char **env, t_data *data)
{
	data->cmd = malloc(sizeof(t_cmd));
	data->tenv = copy_tenv(env);
	display_env(data->tenv);
	data->env = copy_env(env);
}