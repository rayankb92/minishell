/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:47:12 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/11 01:37:29 by jewancti         ###   ########.fr       */
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

		ft_printf("{magenta}Files{reset}:\n");

		ft_printf("\t{yellow}[0] = Redirect to{reset}:\t%s\n", tmp -> files[0] . redirect);
		ft_printf("\t{blue}[0] = Index redirect{reset}:\t%d\n", tmp -> files[0] . index_redirect);
		ft_printf("\t{yellow}[1] = Redirect to{reset}:\t%s\n", tmp -> files[1] . redirect);
		ft_printf("\t{blue}[1] = Index redirect{reset}:\t%d\n", tmp -> files[1] . index_redirect);
		ft_printf("\t{yellow}[2] = Redirect to{reset}:\t%s\n", tmp -> files[2] . redirect);
		ft_printf("\t{blue}[2] = Index redirect{reset}:\t%d\n", tmp -> files[2] . index_redirect);
		ft_printf("\t{yellow}[3] = Redirect to{reset}:\t%s\n", tmp -> files[3] . redirect);
		ft_printf("\t{blue}[3] = Index redirect{reset}:\t%d\n", tmp -> files[3] . index_redirect);

		tmp = tmp -> next;
		ft_printf("\n");
	}
	ft_printf("{red}\t\t---------------------{reset}\n");
}

//ls -a -b > e -f -8 << h > redi -f -h | > e << g