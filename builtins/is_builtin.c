/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:05:34 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/09 04:36:57 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

# define SIZEMATCH	6	

static int	matching(const char *match)
{
	static const char const *matchs[SIZEMATCH] = {
		"cd", "echo", "exit", "export", "pwd", "unset"
	};
	const char const	*tmp;
	int					i;

	i = 0;
	while (i < SIZEMATCH)
	{
		if (ft_strcmp(matchs[i], match) == 0)
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

static void	do_builtin(const char *match, t_cmd *cmd)
{
	if (ft_strcmp("cd", match) == 0)
	{
		if (cmd -> args && ft_strcmp("cd", cmd -> args[0]) == 0 && cmd -> args[1])
			cd(cmd -> args[1]);
		else
			cd("~");
	}
	if (ft_strcmp("echo", match) == 0)
		echo(match, 0);
	if (ft_strcmp("pwd", match) == 0)
		pwd();
	if (ft_strcmp("exit", match) == 0)
		is_exit(cmd -> args);
}

int	is_builtin(t_cmd *cmd)
{
	const char				*match;
	int						ret;

	match = cmd -> command;
	ret = matching(match);
	if (ret == EXIT_SUCCESS)
		do_builtin(match, cmd);
	return (ret == EXIT_FAILURE);
}
