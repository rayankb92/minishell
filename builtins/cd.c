/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:01:50 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/15 04:49:09 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cd(const char *path)
{
	if (!ft_strcmp(path, "~") || !path)
		path = ft_strdup(getenv("HOME"));
	if (chdir(path) == -1)
	{
		//ft_memdel((void **)& path);
		return (perror(path), ft_memdel((void **)& path), -1);
	}
	ft_memdel((void **)& path);
	return (1);
}
