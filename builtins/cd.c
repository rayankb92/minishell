/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:01:50 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/19 23:11:07 by rferradi         ###   ########.fr       */
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
	{
		char *temp = getenv("HOME");
		if (temp)
		{
			change_directory(getenv("HOME"));
			ft_memdel((void **)& temp);
		}
	}
	else
		change_directory(path);
}
