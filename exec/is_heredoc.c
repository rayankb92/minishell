/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:19:49 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/20 10:29:52 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./../include/minishell.h"

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

static
void	write_to_pipe(t_heredoc *tab, int len)
{
	int		i;
	char	*line;

	i = -1;
	//printf("pointeur du heredoc %p\n", tab);
	while (++i < len)
	{
		while (1)
		{
			line = readline("heredoc :");
			if (!line || !ft_strcmp(line, tab[i].limiter))
				break ;
			ft_putendl_fd(line, tab[i].pipe[1]);
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
void	handler(int signum, siginfo_t *client, void *ucontext)
{
	(void)client;
	(void)ucontext;
	if (signum == SIGINT)
	{
		//free_shell((t_data *)ucontext);
		exit(EXIT_SUCCESS);
	}
}

void	is_heredoc(t_data *data, t_cmd *ptr)
{
	pid_t		pid;
	t_saction	saction;
	int		status;
	
	status = 0;
	int e = 214545;

	ft_memset(& saction, 0, sizeof(saction));
	saction.sa_flags = SA_SIGINFO;
	saction.sa_sigaction = handler;
	signal(SIGINT, SIG_IGN);
	data -> len_here = len_here_doc(data -> cmd);
	if (data->len_here == 0)
		return ;
	data -> here_doc = ft_calloc(sizeof(t_heredoc), data -> len_here);
	if (!data -> here_doc)
		return ;
	set_tabs(data -> here_doc, ptr);
	// ft_arraydel(data->herecopy);
	pid = fork();
	if (pid == 0)
	{
		sigaction(SIGINT, &saction, (void *)& e);
		data->expand = 0;
		find_here_doc(data->herecopy, data);
		data->expand = 1;
		//ft_arraydel(data->path);
		write_to_pipe(data -> here_doc, data -> len_here);
		//free((void *)data -> here_doc[0] . limiter);
		//free(data -> here_doc);
		//ft_arraydel(data->env);
		free_shell(data);
		exit(EXIT_SUCCESS);
	}
	close_pipes(data -> here_doc, 0, 1, data -> len_here);
	waitpid(pid, &status, 0);
	signal(SIGINT, SIG_IGN);
	//ft_memdel((void **)& data-> here_doc[0]. limiter);
	//free(data-> here_doc);
	//data->here_doc = NULL;
	//free_heredoc(data -> here_doc, data -> len_here);
}
