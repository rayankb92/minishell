/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:14:28 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/24 14:17:49 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define LLMAX	9223372036854775807LL
#define LLMIN	-9223372036854775807LL

void	is_exit(t_data *data, char **argument)
{
	const char	*tmp;
	long long	res;
	int			index;
	int			a;

	(void)data;
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
			ft_printf("bash: exit: too many arguments\n", tmp);
			update_status_code(data, 127);
			return ;
		}
		if (*tmp != '\0' || res > LLMAX || res < LLMIN)
		{
			ft_printf("bash: exit: %s: numeric argument required\n", tmp);
			free_shell(data);
			exit(2);
		}
	}
	ft_putendl("exit");
	a = EXIT_SUCCESS;
	if (argument[1] != NULL)
		a = ft_atoull(argument[1]) % 256;;
	free_shell(data);
	exit(a);
}
