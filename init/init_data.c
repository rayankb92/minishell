/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:22:50 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/22 06:29:55 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	copy_files(t_data *data)
// {
// 	DIR				*d;
// 	struct dirent	*dir;
// 	int				i;

// 	i = 0;
// 	d = opendir(".");
// 	if (!d)
// 		return ;
// 	dir = readdir(d);
// 	data->dir[i] = dir->d_name;
// 	while (i < 5)
// 	{
// 		data->dir[i++] = dir->d_name;
// 		dir = readdir(d);
// 	}
// 	data->dir[i++] = 0;
// 	ft_displaydouble(data->dir);
// }

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
		{
			data -> tenv = new_env(ft_strdup("?"), ft_strdup("0"), 0);
			char path[4096];
			getcwd(path, 4096);
			ft_strcpy(path, ft_strrchr(path, '/') + 1);
			add_back_env(& data -> tenv, new_env(get_key("OLDPWD"), get_value(path), 1));
		}
		env_set++;
	}
	return (EXIT_SUCCESS);
}
