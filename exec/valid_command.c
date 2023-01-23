/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 00:39:16 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/23 03:31:04 by jewancti         ###   ########.fr       */
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
