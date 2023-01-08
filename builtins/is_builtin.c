/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:05:34 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/08 22:56:29 by jewancti         ###   ########.fr       */
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
}

int	is_builtin(const char *input, t_cmd *cmd)
{
	const char				*copy;
	const char				*begin;
	const char				*match;
	int						ret;

	copy = cmd -> command;
	while (ft_isspace(*copy))
		copy++;
	begin = copy;
	while (*copy && !ft_isspace(*copy))
		copy++;
	if (begin == copy)
		return (0);
	match = ft_strsub(input, begin - input, copy - input);
	ret = matching(match);
	if (ret == EXIT_SUCCESS)
		do_builtin(match, cmd);
	ft_memdel((void **)& match);
	return (ret < 0);
}
