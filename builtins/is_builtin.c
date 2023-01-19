/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:05:34 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/19 13:29:30 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

# define SIZEMATCH	7

static int	matching(const char *match)
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

static void	do_builtin(const char *match, t_cmd *cmd, t_data *data)
{
	if (ft_strcmp("cd", match) == 0)
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
	if (ft_strcmp("echo", match) == 0)
		echo((const char **)cmd -> args + 1, 1);
	if (ft_strcmp("pwd", match) == 0)
		pwd();
	if (ft_strcmp("exit", match) == 0)
		is_exit(cmd -> args);
	if (ft_strcmp("export", match) == 0)
	{	
		char *temp = array_to_string(cmd -> args + 1);
		export(data, temp);
		ft_memdel((void **)& temp);
	}
	if (ft_strcmp("unset", match) == 0)
	{
		for (int i = 1; cmd -> args[i]; i++)
			unset(data, cmd -> args[i]);
	}
	if (ft_strcmp("env", match) == 0)
		display_env(data -> tenv);
}

int	is_builtin(t_cmd *cmd, t_data *data)
{
	const char				*match;
	int						ret;

	match = cmd -> command;
	if (!match)
		return (EXIT_FAILURE);
	ret = matching(match);
	if (ret == EXIT_SUCCESS)
	{
		ft_printf("{red}Executing: Built in ..{reset}\n");
		do_builtin(match, cmd, data);
	}
	return (ret == EXIT_FAILURE);
}
