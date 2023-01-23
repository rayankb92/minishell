/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:19:49 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/23 05:07:31 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

extern void	*g_data;

static
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

static
void	set_tabs(t_heredoc *tab, t_cmd *ptr)
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
				tab[j].limiter = tmp->sequence[i].redirect;
				pipe(tab[j++].pipe);
			}
			i++;
		}
		tmp = tmp -> next;
	}
}

void	print_heredoc(char *str, int fd, int exp, t_data *data)
{
	char	*var;
	int		i;


	i = 0;
	if (!exp)
		ft_putendl_fd(str, fd);
	else
	{
		while (str[i])
		{
			if (str[i] == '$' && str[i + 1] && is_variable(str[i + 1], 1))
			{
				var = expand(data, &str[i + 1]);
				if (var)
				{
					i += get_varname_len(&str[i + 1]);
					ft_putstr_fd(var, fd);
				}
			}
			else
				ft_putchar_fd(str[i], fd);
			i++;
		}
	}
	ft_putchar_fd('\n', fd);
}

static
void	write_to_pipe(t_heredoc *tab, int len, t_data *data)
{
	int		i;
	char	*line;

	i = -1;
	while (++i < len)
	{
		while (1)
		{
			line = readline("heredoc :");
			if (!line || !ft_strcmp(line, tab[i].limiter))
				break ;
			print_heredoc(line, tab[i].pipe[1], tab[i].expand, data);
		}
		free((char *)tab[i].limiter);
		if (tab[i].pipe[1] != -1)
			close(tab[i].pipe[1]);
		if (tab[i].pipe[0] != -1)
			close(tab[i].pipe[0]);
	}
}

void	close_pipes(t_heredoc *tab, int read, int write, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (write && tab[i].pipe[1] != -1)
			close(tab[i].pipe[1]);
		if (read && tab[i].pipe[0] != -1)
			close(tab[i].pipe[0]);
	}
}

int		find_pipe(t_heredoc *tab, const char *limiter, int len)
{
	int	i;

	i = -1;
	if (!tab || !tab[0].limiter)
		return (-1);
	while (++i < len)
	{
		if (limiter == tab[i].limiter)
			break ;
	}
	return (tab[i].pipe[0]);
}



static
void	exit_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar('\n');
		free_shell(((t_data *)g_data));
		close_pipes(((t_data *)g_data) -> here_doc, 1, 1, ((t_data *)g_data) -> len_here);
		exit(130);
	}
}

void	is_heredoc(t_data *data, t_cmd *ptr)
{
	pid_t		pid;

	data -> len_here = len_here_doc(data -> cmd);
	if (data->len_here == 0)
		return ;
	data -> here_doc = ft_calloc(sizeof(t_heredoc), data -> len_here);
	if (!data -> here_doc)
		return ;
	signal(SIGINT, SIG_IGN);
	set_tabs(data -> here_doc, ptr);
	// ft_arraydel(data->herecopy);
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		signal(SIGINT, & exit_heredoc);
		data->expand = 0;
		find_here_doc(data->herecopy, data);
		data->expand = 1;
		//ft_arraydel(data->path);
		write_to_pipe(data -> here_doc, data -> len_here, data);
		//free((void *)data -> here_doc[0] . limiter);
		//free(data -> here_doc);
		//ft_arraydel(data->env);
		free_shell(data);
		exit(EXIT_SUCCESS);
	}
	close_pipes(data -> here_doc, 0, 1, data -> len_here);
	waitpid(pid, & data->signal, 0);
	if (WIFEXITED(data->signal))
		data->signal = WEXITSTATUS(data->signal);
	signal(SIGINT, SIG_IGN);
	//ft_memdel((void **)& data-> here_doc[0]. limiter);
	//free(data-> here_doc);
	//data->here_doc = NULL;
	//free_heredoc(data -> here_doc, data -> len_here);
}

/*\*/