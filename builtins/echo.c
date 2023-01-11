/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:50:48 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/11 02:25:56 by rferradi         ###   ########.fr       */
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

void	echo(const char *arg, const char c)
{
	// if (is_valid_option(arg[0]))
	// 	return ;
	// if (arg[0] == '\0' || !arg || !*arg)
	// 	return (write(1, " ", 1));
	
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

void	_echo(const char **arg)
{
	int i = 0;
	
	while (arg[i] && is_valid_option(arg[i]))
		i++;
	print(arg, i);
}


// [-nnnnnnno] [woiejoiwe] [sdij]