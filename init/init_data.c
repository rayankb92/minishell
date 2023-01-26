/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:22:50 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/26 19:00:26 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static
int	set_no_env(t_data *data)
{
	t_env	*tenv;
	char	*find;

	data -> tenv = new_env(ft_strdup("?"), ft_strdup("0"), 0);
	if (!data -> tenv)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static
int	set_env(t_data *data, char **env, int *env_set)
{
	if ((*env_set) == 0)
	{
		if (env && *env)
		{
			data -> tenv = copy_tenv(env);
			if (tenv_to_env(data, env))
				return (EXIT_FAILURE);
		}
		else
			set_no_env(data);
		(*env_set)++;
	}
	return (EXIT_SUCCESS);
}

int	init_data(t_data *data, char **env)
{
	static int	env_set = 0;

	if (!env_set)
		ft_bzero(data, sizeof(t_data));
	data -> cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!data)
		return (EXIT_FAILURE);
	data -> prev_pipe = -1;
	data -> pipes[0] = -1;
	data -> pipes[1] = -1;
	data -> path = 0;
	return (set_env(data, env, & env_set));
}


/*
je suis un! bateau
bateau un! suis je

*/