/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:33:46 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/24 10:58:25 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

#ifndef PATH_MAX
 # define PATH_MAX	10000
#endif

void	pwd(void)
{
	static char		path[PATH_MAX] = {0};

	getcwd(path, PATH_MAX);
	if (path[0])
		ft_putendl(path);
}

char	*pwd_malloc(void)
{
	char		*path;

	path = 0;
	return (ft_strdup(getcwd(path, PATH_MAX)));
}
