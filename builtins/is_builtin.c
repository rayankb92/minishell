/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:05:34 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/21 17:40:29 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

# define SIZEMATCH	7

int	matching(const char *match)
{
	static const char	*matchs[SIZEMATCH] = {
		"cd", "echo", "exit", "export", "pwd", "unset", "env"
	};
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

void	do_builtin(t_cmd *cmd, t_data *data)
{
	if (ft_strcmp("cd", cmd -> command) == 0)
	{
		if (cmd -> args[1] && cmd -> args[2])
		{
			ft_putendl_fd("bash: cd: too many arguments", 2);
			return ;
		}
		if (ft_strcmp("cd", cmd -> args[0]) == 0 && cmd -> args[1])
			cd(cmd -> args[1]);
		else
			cd("~");
	}
	if (ft_strcmp("echo", cmd -> command) == 0)
		echo((const char **)cmd -> args + 1, 1);
	if (ft_strcmp("pwd", cmd -> command) == 0)
		pwd();
	if (ft_strcmp("exit", cmd -> command) == 0)
		is_exit(data, cmd -> args);
	if (ft_strcmp("export", cmd -> command) == 0)
	{
		for (int i = 1; cmd -> args[i]; i++)
			export(data, cmd -> args[i], 0);
	}
	if (ft_strcmp("unset", cmd -> command) == 0)
	{
		for (int i = 1; cmd -> args[i]; i++)
			unset(data, cmd -> args[i]);
	}
	if (ft_strcmp("env", cmd -> command) == 0)
		display_env(data -> tenv);
}

int	is_builtin(t_cmd *cmd)
{
	const char				*match;

	match = cmd -> command;
	if (!match)
		return (EXIT_FAILURE);
	return (matching(match));
}
