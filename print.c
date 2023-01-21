/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:47:12 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/21 18:11:59 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	if (!tmp)
		return ;
	ft_printf("\n\n\t\t{cyan}---------------------{reset}\n");
	while (tmp)
	{
		ft_printf("{magenta}Command{reset}:\t%s\n", tmp -> command);
		//ft_printf("Temp args: [%s]\n", tmp -> temp_args);
		if (tmp -> args)
		for (int i = 0; tmp -> args[i]; i++)
			ft_printf("\tArg[%d]:\t\t[%s]\n", i, tmp -> args[i]);
	
		for (int i = 0; i < tmp -> length_sequence; i++)
		{
			ft_printf("{green}Sequence{reset}[{cyan}%d{reset}]:\n", i);
			ft_printf("\t{yellow}Redirect to{reset}:\t%s\n", tmp -> sequence[i] . redirect);
			ft_printf("\t{blue}Index redirect{reset}:\t%d\n", tmp -> sequence[i] . index_redirect);
		}
		tmp = tmp -> next;
		ft_printf("\n");
	}
	ft_printf("{red}\t\t---------------------{reset}\n");
}

void	display_env(t_env *env)
{
	t_env *temp;

	temp = env;
	while (temp)
	{
		if (temp -> key && temp -> value && temp->value[0])
		{
			ft_putstr(temp -> key);
			ft_putchar('=');
			ft_putendl(temp -> value);
		}
		else if (temp -> key && temp -> equal == 0)
		{
			ft_putstr(temp -> key);
			ft_putendl("=");
		}
		temp = temp -> next;
	}
}

void	display_lst(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		ft_printf("%s\n", tmp -> content);
		tmp = tmp -> next;
	}
}
