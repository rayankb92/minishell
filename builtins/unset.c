/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 01:38:06 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/22 03:37:59 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	unset(t_data *data, const char *key)
{
	t_env	*tmp;
	t_env	*copy;

	tmp = data -> tenv;
	copy = data -> tenv;
	if (key[0] == '?')
		return ;
	while (copy)
	{
		if (copy -> key && ft_strcmp(copy -> key, key) == 0)
		{
			if (copy -> next)
				tmp -> next = copy -> next;
			else
				tmp -> next = 0;
			ft_memdel((void **)& copy -> key);
			ft_memdel((void **)& copy -> value);
			ft_memdel((void **)& copy);
			return ;
		}
		tmp = copy;
		copy = copy -> next;
	}
}
