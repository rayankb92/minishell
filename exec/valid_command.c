/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 00:39:16 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/22 20:52:40 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*valid_command(const char *command, char **env)
{
	int			i;
	char	*joined;

	if (!command || !env)
		return (NULL);
	i = -1;
	joined = 0;
	if (ft_strchr(command, '/'))
	{
		joined = ft_strdup(command);
		if (access(joined, F_OK ) == -1) //("file exist")
			ft_putstr_fd("No such file or directory\n", 1);
		else if (access(joined, X_OK | R_OK) == -1)
			ft_putstr_fd("Permission denied\n", 1);
		ft_memdel((void **)& joined);
	}
	while (command && env[++i])
	{
		joined = ft_strjoin(env[i], "/");
		ft_realloc(& joined, command);
		if (access(joined, X_OK) == 0)
			return (joined);
		ft_memdel((void **)& joined);
	}
	return (NULL);
}
