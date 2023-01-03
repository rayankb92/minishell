/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:33:46 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/01 11:42:20 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

const char	*pwd(void)
{
	char		*path;
	int			i;

	path = calloc(1, 1);
	if (!path)
		return (0);
	i = 0;
	while (1)
	{
		if (getcwd(path, i))
			break ;
		free(path);
		path = calloc(i, 1);
		i++;
	}
	return ((const char *)path);
}