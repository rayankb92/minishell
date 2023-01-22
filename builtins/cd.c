/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:01:50 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/22 03:16:54 by rferradi         ###   ########.fr       */
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
	if ((!path || ft_strcmp(path, "~") == 0 )&& getenv("HOME"))
		change_directory(getenv("HOME"));
	else
		change_directory(path);
}
