/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:01:50 by rferradi          #+#    #+#             */
/*   Updated: 2022/12/31 14:34:55 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cd(const char *path)
{
	if (!ft_strcmp(path, "~") || !path)
		path = ft_strdup(getenv("HOME"));
	if (chdir(path) == -1)
		return (perror(path), -1);
	return (1);
}