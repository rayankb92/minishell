/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 23:18:11 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/22 19:38:33 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

static
void	dup_or_printerr(const int fd, const int redirect, const char *error)
{
	if (fd < 0)
		ft_putendl_fd(error, 2);
	else if (fd > 2)
	{
		dup2(fd, redirect);
		close(fd);
	}
}

int	is_redirection(t_data *data, t_cmd *ptr)
{
	static const int	indexs[3] = {
		O_WRONLY | O_CREAT | O_TRUNC, 
		O_WRONLY | O_CREAT | O_APPEND,
		O_RDONLY
	};
	int					fd;
	int					index_redirect;
	int					i;
	int					j;

	i = 0;
	j = 0;
	while (i < ptr -> length_sequence)
	{
		index_redirect = ptr -> sequence[i] . index_redirect;
		if (ptr -> sequence[i] . redirect != NULL)
		{
			fd = -1;
			if (index_redirect != DLESS)
				fd = open(ptr -> sequence[i] . redirect, indexs[index_redirect - 1], 0666);
			else
			{
				if (data -> len_here != 0)
					fd = find_pipe(data -> here_doc, data -> here_doc[j].limiter, data -> len_here);
				j++;
			}
			if (fd < 0)
			{
				if (errno == 13)
					ft_printf("bash: %s: PERMISSION DENIED\n", ptr -> sequence[i] . redirect);
				else
				ft_printf("bash: %s: No such file or directory\n", ptr -> sequence[i] . redirect);
				if (data -> cmd && data -> cmd -> next)
				{
					free_shell(data);
					exit(EXIT_FAILURE);
				}
				else
					return 1;
			}
			if (index_redirect != LESS && index_redirect != DLESS)
				dup_or_printerr(fd, STDOUT_FILENO, "Cannot open great / dgreat");
			else
				dup_or_printerr(fd, STDIN_FILENO, "Cannot open less / dless");
		}
		i++;
	}
	// update_status_code(data, 0);
	return (0);
}

/*
ls> ""a
*/