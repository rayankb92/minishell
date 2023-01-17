/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:41:08 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/17 07:23:06 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		cmd_tmp = cmd -> next;
		ft_memdel((void **)& cmd -> command);
		ft_arraydel(cmd -> args);
		for (int i = 0; i < cmd -> length_sequence; i++)
			ft_memdel((void **)& cmd -> sequence[i] . redirect);
		ft_memdel((void **)& cmd -> sequence);
		ft_memdel((void **)& cmd);
		cmd = cmd_tmp;
	}
}

void	free_shell(t_data *data)
{
	ft_arraydel(data -> path);
	ft_arraydel(data -> env);
	free_tenv(data -> tenv);
	free_cmd(data -> cmd);
	data -> cmd = 0;
	data -> tenv = 0;
	data -> path = 0;
	data -> env = 0;
}
