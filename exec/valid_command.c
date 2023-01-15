/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 00:39:16 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/14 00:39:40 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	valid_command(const char *command, const char **env)
{
	int			i;
	char	*joined;

	i = -1;
	joined = 0;
	while (command && env[++i])
	{
		if (ft_strchr(command, '/'))
			joined = ft_strdup(command);
		else
			joined = ft_strjoin(env[i], command);
		if (access(joined, X_OK) == 0)
		{
			ft_memdel((void **)& joined);
			return (i);
		}
		ft_memdel((void **)& joined);
	}
	return (-1);
}
