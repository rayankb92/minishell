/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:22:50 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/19 13:20:04 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_data(t_data *data, char **env)
{
	static int	env_set = 0;

	if (!env_set)
		ft_bzero(data, sizeof(t_data));
	else
		data -> cmd = 0;
	data -> cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!data)
		return (EXIT_FAILURE);
	data -> prev_pipe = -1;
	data -> pipes[0] = -1;
	data -> pipes[1] = -1;
	data -> path = 0;
	if (env_set == 0)
	{
		if (env && *env)
		{
			data -> tenv = copy_tenv(env);
			tenv_to_env(data, env);
		}
		else
			data -> tenv = ft_calloc(sizeof(t_env), 1);
		env_set++;
	}
	return (EXIT_SUCCESS);
}
