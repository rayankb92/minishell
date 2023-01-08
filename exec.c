/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:52:31 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/08 22:30:31 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

# define TEMP_PATH = "/usr/bin/"

void	exec(const char *input, t_cmd *cmd)
{
	if (is_builtin(input, cmd) == EXIT_FAILURE)
	{
		// exec
	}
}
