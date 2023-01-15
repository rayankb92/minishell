/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:41:08 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/15 04:46:50 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static
void	free_tenv(t_env *ptr)
{
	t_env	*tmp;

	while (ptr)
	{
		tmp = ptr -> next;
		ft_memdel((void **)& ptr -> key);
		ft_memdel((void **)& ptr -> value);
		ft_memdel((void **)& ptr);
		ptr = tmp;
	}
	ft_memdel((void **)& ptr);
}

void	free_cmd(t_cmd *ptr)
{
	t_cmd	*cmd;
	t_cmd	*cmd_tmp;

	cmd = ptr;
	while (cmd)
	{
		//ft_printf(">> command: %s\n", cmd -> command);
		ft_memdel((void **)& cmd -> command);
		//ft_printf(">> command: %s\n", cmd -> command);
		cmd_tmp = cmd -> next;
		//if (cmd -> args) {
		//	for (int i = 0; cmd -> args[i]; i++)
		//		free(cmd -> args[i]);
		//	free(cmd -> args);
		//}
		ft_arraydel(cmd -> args);
		cmd -> args = 0;
		//for (int i = 0; i < cmd -> length_sequence; i++)
		//	ft_memdel((void **)& cmd -> sequence[i] . redirect);
		ft_memdel((void **)& cmd -> sequence);
		ft_memdel((void **)& cmd);
		cmd = cmd_tmp;
	}
}

void	free_shell(t_data data)
{
	t_env	*env;
	t_env	*env_tmp;

	env = data.env;
	while (env)
	{
		env_tmp = env -> next;
		ft_memdel((void **)& env -> key);
		ft_memdel((void **)& env -> value);
		ft_memdel((void **)& env);
		env = env_tmp;
	}
	free_cmd(data . cmd);
}
