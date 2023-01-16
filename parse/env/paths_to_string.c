/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_to_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 23:14:13 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/16 04:58:00 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

const char	**set_paths(char **paths, int *size)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = ft_strjoin(paths[++i] + 5, "/");
	if (!tmp)
		return (0);
	ft_memdel((void **)& paths[i]);
	paths[i] = tmp;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (0);
		ft_memdel((void **)& paths[i]);
		paths[i] = tmp;
	}
	*size = i;
	return ((const char **)paths);
}

const char	**env_paths_to_string(char **env, int *size)
{
	int		i;
	int		j;
	char	*tmp;
	char	**paths;

	i = -1;
	*size = 0;
	while (env[++i])
	{
		if (ft_strnstr(env[i], "PATH", 4))
		{
			paths = ft_split(env[i], ':');
			if (!paths)
				break ;
			return (set_paths(paths, size));
		}
	}
	return (0);
}
