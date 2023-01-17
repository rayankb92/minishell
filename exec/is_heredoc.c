/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:19:49 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/17 12:32:23 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

void	is_heredoc(t_data *data, t_cmd *ptr)
{
	char	*tmp = 0;
	char	*entry = 0;
	int		i;

	i = 0;
	int fd = open("test.fumier", O_CREAT | O_TRUNC | O_WRONLY);
	while (i < ptr -> length_sequence)
	{
		if (ptr -> sequence[i] . index_redirect == DLESS)
		{
			char	*stop = ft_strjoin(ptr -> sequence[i] . redirect, "\n");
			while (1)
			{
				entry = get_next_line(0, 0);
				ft_realloc(& tmp, entry);
				if (tmp && entry && ft_strcmp(entry, stop) == 0)
					break ;
			}
			ft_memdel((void **)& stop);
			ft_putstr_fd(entry, fd);
			dup2(fd, STDOUT_FILENO);
			ft_memdel((void **)& entry);
		}
		i++;
	}
	//ft_memdel((void **)& entry);
}
