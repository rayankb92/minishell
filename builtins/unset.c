/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 01:38:06 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/18 21:01:58 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	var_name_len(char *name)
{
	size_t	i;

	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	return (i);
}

int	unset(t_data *data, char *name)
{
	(void)data;
	(void)name;
	//size_t	len;
	//t_list	*tmp;
	//t_list	*del;

	//len = var_name_len(name);
	//while (tmp)
	//{
	//	if (tmp->next && ft_strncmp(name, tmp->next->content, len) == 0)
	//	{
	//		del = tmp->next;
	//		tmp->next = tmp->next->next;
	//		ft_memdel((void **)& del->content);
	//		ft_memdel((void **)& del);
	//		break ;
	//	}
	//	tmp = tmp->next;
	//}
	return (1);
}

// rayan=okok
// J=wefwe
// moha=2efois