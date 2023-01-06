/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:52:31 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/05 19:15:35 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

# define TEMP_PATH = "/usr/bin/"

void	exec(t_cmd *cmd)
{
	char		*match;

	match = 0;
	if (is_specifier(cmd -> command, & match) == EXIT_SUCCESS)
	{
		// hard code TST
		if (ft_strcmp(match, "cd") == 0)
		{
			cd(cmd -> temp_args);
			ft_printf("%s\n", pwd());
		}
	}
	//char * path = ft_strjoin(cmd -> command);
}