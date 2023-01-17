/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:19:49 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/17 04:52:33 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

void	is_heredoc(t_data *data, t_cmd *ptr)
{
	int		i;
	char	c;

	i = 0;
	while (i < ptr -> length_sequence)
	{
		if (ptr -> sequence[i] . index_redirect == DLESS)
		{
			char	*tmp;
			char	*entry;
			char	*stop = ft_strjoin(ptr -> sequence[i] . redirect, "\n");
			while (1)
			{
				ft_printf("input: %s | stop: %s\n", tmp, stop);
				entry = get_next_line(0, 0);
				ft_realloc(& tmp, entry);
				if (tmp && entry && ft_strcmp(entry, stop) == 0)
					break ;
			}
			//dup2()
		}
		i++;
	}
}
