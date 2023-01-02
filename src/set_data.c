/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:22:50 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/02 11:37:35 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*copy_env(char **env)
{
	int		i;
	t_list	*new;

	i = 0;
	new = ft_lstnew(env[i]);
	while (env[++i])
		ft_lstadd_back(&new, ft_lstnew(env[i]));
	return (new);
}

void		set_data(char **env, t_data *data)
{
	data->env = copy_env(env);
}