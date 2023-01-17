/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:14:28 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/17 09:37:49 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define LLMAX	9223372036854775807LL
#define LLMIN	-9223372036854775807LL

void	is_exit(char **argument)
{
	const char	*tmp;
	long long	res;
	int			index;

	if (!argument || !*argument)
	{
		ft_putendl("exit");
		return ;
	}
	index = 0;
	while (argument[++index])
	{
		tmp = argument[index];
		res = ft_atoull(tmp);
		if (*tmp == '+' || *tmp == '-')
			tmp ++;
		while (ft_isdigit(*tmp))
			tmp++;
		if (index > 1)
		{
			ft_putendl("exit");
			ft_printf("bash: exit: too many arguments\n", tmp); // status code 1
			return ;
			//exit(1);
		}
		if (*tmp != '\0' || res > LLMAX || res < LLMIN)
		{
			ft_printf("bash: exit: %s: numeric argument required\n", tmp);
			exit(2);
		}
	}
	ft_putendl("exit");
	if (argument[1])
		exit(ft_atoull(argument[1]) % 256);
	exit(EXIT_SUCCESS);
}
