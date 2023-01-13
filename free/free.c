/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:41:08 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/12 19:21:34 by jewancti         ###   ########.fr       */
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

static
void	free_env(t_list *ptr)
{
	t_list	*tmp;

	while (ptr)
	{
		tmp = ptr -> next;
		ft_memdel((void **)& ptr -> content);
		ft_memdel((void **)& ptr);
		ptr = tmp;
	}
	ft_memdel((void **)& ptr);
}

void	free_cmd(t_cmd *ptr)
{
	t_cmd	*tmp;

	while (ptr)
	{
		ft_memdel((void **)& ptr -> sequence);
		tmp = ptr -> next;
		ft_memdel((void **)& ptr);
		ptr = tmp;
	}
	ft_memdel((void **)& ptr);
}

void	free_minishell(t_data data)
{
	t_cmd	*cmd;
	t_env	*tenv;
	t_list	*env;

	cmd = data.cmd;
	tenv = data.tenv;
	env = data.env;
	if (cmd)
		free_cmd(cmd);
	if (env)
		free_env(env);
	if (tenv)
		free_tenv(tenv);
}