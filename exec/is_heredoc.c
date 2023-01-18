/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:19:49 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/18 06:27:17 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./../include/minishell.h"


int	len_here_doc(t_cmd *ptr)
{
	int		len;
	int		i;
	t_cmd	*tmp;
	
	tmp = ptr;
	len = 0;
	while (tmp)
	{
		i = 0;
		while (i < tmp -> length_sequence)
		{
			if (tmp -> sequence[i] . index_redirect == DLESS)
				len++;
			i++;
		}
		tmp = tmp -> next;
	}
	return (len);
}

void	close_pipes(t_heredoc **tab, int read, int write)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		if (write)
			close(tab[i]->pipe[1]);
		if (read)
			close(tab[i]->pipe[0]);
	}
}

void	set_tabs(t_heredoc **tab, t_cmd *ptr)
{
	t_cmd	*tmp;
	int		i;
	int		j;

	j = 0;
	tmp = ptr;
	while (tmp)
	{
		i = 0;
		while (i < tmp -> length_sequence)
		{
			if (tmp -> sequence[i] . index_redirect == DLESS)
			{
				tab[j] = ft_calloc(sizeof(t_heredoc), 1);
				if (!tab[j])
					return ;
				tab[j]->limiter = tmp->sequence[i].redirect;
				pipe(tab[j++]->pipe);
			}
			i++;
		}
		tmp = tmp -> next;
	}
}

void	write_to_pipe(t_heredoc **tab, int len)
{
	int		i;
	char	*line;

	i = -1;
	while (tab[++i])
	{
		while (1)
		{
			line = readline("heredoc :");
			if (!line || !ft_strcmp(line, tab[i]->limiter))
				break ;
			ft_putendl_fd(line, tab[i]->pipe[1]);
		}
		close(tab[i]->pipe[1]);
		close(tab[i]->pipe[0]);
	}
	exit(0);
}

void	is_heredoc(t_data *data, t_cmd *ptr)
{
	pid_t	pid;
	int		status;
	
	status = 0;
	data -> len_here = len_here_doc(data -> cmd);
	data -> tab = ft_calloc(sizeof(t_heredoc*), data -> len_here + 1);
	if (!data -> tab)
		return ;
	set_tabs(data -> tab, ptr);
	pid = fork();
	if (pid == 0)
		write_to_pipe(data -> tab, data -> len_here);
	close_pipes(data -> tab, 0, 1);
	waitpid(pid, &status, 0);
	//ft_memdel((void **)& entry);
}

int		find_pipe(t_heredoc **tab, char *limiter, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (limiter == tab[i]->limiter)
			break ;
	}
	return (tab[i]->pipe[0]);
}