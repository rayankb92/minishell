/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:33:46 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/14 11:10:35 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pwd(void)
{
	static char		path[4096] = {0};

	getcwd(path, 4096);
	if (path[0])
		ft_putendl(path);
}

const char	*pwd_malloc(void)
{
	char		path[4096];

	return (ft_strdup(getcwd(path, 4096)));
}
