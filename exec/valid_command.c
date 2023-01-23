/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 00:39:16 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/23 08:30:30 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*path_cmd(const char *command)
{
	char	*joined;

	joined = ft_strdup(command);
	if (access(joined, F_OK) == -1)
		ft_printf("%s: No such file or directory\n", command);
	else if (access(joined, X_OK | R_OK) == -1)
		ft_printf("%s: Permission denied\n", command);
	else
		return (joined);
	ft_memdel((void **)& joined);
	return (NULL);
}

static char	*simple_cmd(const char *command, char **env)
{
	int		i;
	char	*joined;

	i = -1;
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

char	*valid_command(const char *command, char **env)
{
	char	*joined;

	if (!command || !env)
		return (NULL);
	if (ft_strchr(command, '/'))
		return (path_cmd(command));
	else
		return (simple_cmd(command, env));
}

// char	*valid_command(const char *command, char **env)
// {
// 	int			i;
// 	char	*joined;

// 	if (!command || !env)
// 		return (NULL);
// 	i = -1;
// 	joined = 0;
// 	if (ft_strchr(command, '/'))
// 	{
// 		joined = ft_strdup(command);
// 		if (access(joined, F_OK ) == -1)
// 			ft_printf("%s: No such file or directory\n", command);
// 		else if (access(joined, X_OK | R_OK) == -1)
// 			ft_printf("%s: Permission denied\n", command);
// 		else
// 			return (joined);
// 	}
// 	ft_memdel((void **)& joined);
// 	while (command && env[++i])
// 	{
// 		joined = ft_strjoin(env[i], "/");
// 		ft_realloc(& joined, command);
// 		if (access(joined, X_OK) == 0)
// 			return (joined);
// 		ft_memdel((void **)& joined);
// 	}
// 	return (NULL);
// }
