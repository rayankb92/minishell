/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:01:50 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/20 00:45:37 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static
void	change_directory(const char *path)
{
	if (chdir(path) == -1)
		perror(path);
	
}

void	cd(const char *path)
{
	if (!path || ft_strcmp(path, "~") == 0)
		change_directory(getenv("HOME"));
	else
		change_directory(path);
}
