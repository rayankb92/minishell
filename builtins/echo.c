/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:50:48 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/15 22:19:40 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_valid_option(const char *opt)
{
	int	i;

	i = 0;
	if (!opt || !opt[0])
		return (0);
	if (opt[i++] != '-')
		return (0);
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void print(const char **arg, int i)
{
	int boolean;

	boolean = (i > 0);
	while (arg[i])
	{
		if (arg[i + 1])
			ft_printf("%s ", arg[i]);
		else
			ft_printf("%s", arg[i]);
		i++;
	}
	if (!boolean)
		ft_printf("\n");
}

void	echo(const char **arg)
{
	int i = 0;
	
	while (arg[i] && is_valid_option(arg[i]))
		i++;
	print(arg, i);
}


// [-nnnnnnno] [woiejoiwe] [sdij]