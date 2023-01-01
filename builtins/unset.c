/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 01:38:06 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/01 23:53:39 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	var_name_len(char *name)
{
	int	i;

	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	return (i);
}

int	unset(t_data *data, char *name)
{
	int	len;
	t_list	*tmp;

	tmp = data->env;
	len = var_name_len(name);
	while (tmp)
	{
		if (tmp->next && ft_strncmp(name, tmp->next->content, len) == 0)
		{
			free(tmp->next->content);
			tmp->next = tmp->next->next;
			break;
		}
		tmp = tmp->next;
	}
}

// rayan=okok
// J=wefwe
// moha=2efois