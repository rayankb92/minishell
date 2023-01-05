/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:35:41 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/05 12:47:39 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	export(t_data *data, char *name, char *value)
{
	char	*export;
	int		len;
	t_list	*tmp;

	tmp = data->env;
	len = ft_strlen(name);
	export = ft_strjoin(ft_strjoin(name, "="), value);
	while (tmp)
	{
		if (ft_strncmp(name, tmp->content, len) == 0 && tmp->content[len] == '=')
		{
			tmp->content = export;
			break;
		}
		if (!tmp->next)
		{
			tmp->next = ft_lstnew(export);
			tmp->next->next = NULL;
			break;
		}
		tmp = tmp->next;
	}
}