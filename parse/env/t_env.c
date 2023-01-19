/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 07:59:57 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/19 08:05:20 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

static
char	*get_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

static
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
		add_back_env(& new, new_env(get_key(env[i]), get_value(env[i]), 1));
	}
	return (new);
}

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
