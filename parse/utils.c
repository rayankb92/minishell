/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 06:37:10 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/17 20:35:43 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_lstcount(t_cmd *cmd)
{
	t_cmd	*ptr;
	int		i;

	ptr = cmd;
	i = 0;
	while (ptr)
	{
		i++;
		ptr = ptr -> next;
	}
	return (i);
}

int	is_in_charset(char c, char *charset)
{
	int	i;

	i = -1;
	while (charset[++i] && charset[i] != c)
		;
	return (c == charset[i]);
}

int	error_msg(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}
//0780865020