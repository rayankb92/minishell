/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 23:18:11 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/12 17:28:46 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

static
void	dup_or_printerr(const int fd, const int redirect, const char *error)
{
	if (fd < 0)
		ft_putendl_fd(error, 2);
	else
		dup2(fd, redirect);
}

static
void	redirect(t_cmd *ptr, const int indexs[3])
{
	int	*fds;
	int	i;

	fds = (int [3]){-1, -1, -1};// DGREAT A LA PRIORITE SUR GREAT
	if (ptr -> files[DGREAT - 1] . index_redirect != -1)
	{
		fds[DGREAT - 1] = open(ptr -> files[DGREAT - 1] . redirect, indexs[ptr -> files[DGREAT - 1] . index_redirect - 1], 0644);
		dup_or_printerr(fds[DGREAT - 1], STDOUT_FILENO, "Cannot open dgreat");
	}
	else if (ptr -> files[GREAT - 1] . index_redirect != -1)
	{
		fds[GREAT - 1] = open(ptr -> files[GREAT - 1] . redirect, indexs[ptr -> files[GREAT - 1] . index_redirect - 1], 0644);
		dup_or_printerr(fds[GREAT - 1], STDOUT_FILENO, "Cannot open great");
	}
	if (ptr -> files[LESS - 1] . index_redirect != -1)
	{
		fds[LESS - 1] = open(ptr -> files[LESS - 1] . redirect, indexs[ptr -> files[LESS - 1] . index_redirect - 1], 0644);
		dup_or_printerr(fds[LESS - 1], STDIN_FILENO, "Cannot open less");
	}
	i = -1;
	while (++i < LESS)
	{
		if (fds[i] > 0)
			close(fds[i]);
	}
}

void	is_redirection(t_cmd *ptr)
{
	static const int	indexs[3] = {
		O_WRONLY | O_CREAT | O_TRUNC, 
		O_WRONLY | O_CREAT | O_APPEND,
		O_RDONLY
	};
	int					fd;
	int					i;

	if (ptr -> sequence)
	{
		i = 0;
		while (i < ptr -> length_sequence)
		{
			if (ptr -> sequence[i] . redirect != ptr -> files[0] . redirect
				&& ptr -> sequence[i] . redirect != ptr -> files[1] . redirect
				&& ptr -> sequence[i] . redirect != ptr -> files[2] . redirect)
			{
				fd = open(ptr -> sequence[i] . redirect, indexs[ptr -> sequence[i] . index_redirect - 1], 0644);
				if (fd < 0)
					ft_putendl_fd("Cannot open file1", 2);
				else
					close(fd);
			}
			i++;
		}
		redirect(ptr, indexs);
	}
}
