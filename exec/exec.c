/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:52:31 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/21 18:26:50 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

static
void	close_fd(int (*fd)[2])
{
	if ((*fd)[0] != -1)
		close((*fd)[0]);
	if ((*fd)[1] != -1)
		close((*fd)[1]);
}

static
void	pipe_redirection(t_data *data, const int index_pid)
{
	const int	lstcount = ft_lstcount(data -> cmd);

	if (index_pid != 0 && data -> prev_pipe != -1)
	{
		dup2(data -> prev_pipe, STDIN_FILENO);
		close(data -> prev_pipe);
	}
	if (index_pid != lstcount - 1)
		dup2(data -> pipes[1], STDOUT_FILENO);
	close_fd(& data -> pipes);
}

static
void	is_child(t_data *data, t_cmd *ptr, int index_pid)
{
	char	*command;
	int		tmp;

	command = valid_command(ptr -> command, data -> path);
	tmp = 0;
	if (!command && ptr -> command && matching(ptr -> command) && !ft_strchr(ptr -> command, '/'))
	{
		update_status_code(data, 127);
		ft_printf("%s: command not found\n", ptr -> command, tmp += 1);
	}
	else
	{
		pipe_redirection(data, index_pid);
		is_redirection(data, ptr);
		if (is_builtin(ptr) == EXIT_FAILURE || ft_strcmp(ptr -> command, "env") == 0)
		{
			if (ft_strcmp(ptr -> command, "env"))
			{
				if (ptr -> command && ptr -> command[0])
				{
					if (ft_strchr(ptr -> command, '/'))
						execve(ptr -> command, ptr -> args, data -> env);
					else
						execve(command, ptr -> args, data -> env);
				}
			}
			else
				do_builtin(ptr, data);
		}
		else
			do_builtin(ptr, data);

	}
	if (13 == errno && !tmp && ptr -> command && ptr -> args[1])
	{
		update_status_code(data, 13);
		ft_printf("%s: %s: Permission denied\n", ptr -> command, ptr -> args[1]); // status code 1
	}
	if (1 == errno && !tmp && ptr -> command && ptr -> args[1])
	{
		update_status_code(data, 1);
		ft_printf("%s: %s: No such file or directory\n", ptr -> command, ptr -> args[1]); //status 1
	}
	close_fd(& data -> pipes);
	ft_memdel((void **)& command);
	free_shell(data);
}

static
void	is_father(t_data *data)
{
	if (data -> prev_pipe != -1)
		close(data -> prev_pipe);
	if (data -> pipes[1] != -1)
		close(data -> pipes[1]);
	data -> prev_pipe = data -> pipes[0];
}


void	exec(t_data *data)
{
	t_cmd		*ptr;
	int			index_pid;
	int			status;
	static int rayan = 0;

	ptr = data -> cmd;
	status = 0;
	index_pid = 0;
	is_heredoc(data, ptr);
	set_path_from_tenv(data);
	while (ptr)
	{
		if (! data -> cmd -> next && is_builtin(ptr) == EXIT_SUCCESS && ft_strcmp(ptr -> command, "env"))
		{
			int copy = dup(STDOUT_FILENO);
			is_redirection(data, ptr);
			do_builtin(ptr, data);
			dup2(copy, STDOUT_FILENO);
			close(copy);
			return ;
		}
		if (pipe(data -> pipes) < 0)
			return ;
		signal(SIGINT, SIG_IGN);
		data -> pids[index_pid] = fork();
		if (data -> pids[index_pid] == -1)
		{
			close_fd(& data -> pipes);
			free_shell(data);
			exit(EXIT_FAILURE);
		}
		if (data -> pids[index_pid] == 0)
		{
			signal(SIGINT, & ctrlc);
			signal(SIGQUIT, & reactiv);
			is_child(data, ptr, index_pid);
			//ft_printf("KEY: %s | %s\n", ft_strdup(get_key_from_tenv(data -> tenv, "?")), ft_strdup(get_key_from_tenv(data -> tenv, "$?")));
			//int status = ft_atoi(get_key_from_tenv(data -> tenv, "?"));
			exit(0);
		}
		if (data -> pids[index_pid] > 0)
		{
			is_father(data);
			signal(SIGQUIT, SIG_IGN);
		}
		index_pid++;
		ptr = ptr -> next;
	}
	close_fd(& data -> pipes);
	if (data -> len_here != 0)
		close_pipes(data -> here_doc, 1, 0, data -> len_here);
	for (int i = 0; i < index_pid; i++)
	{
		waitpid(data -> pids[i], & status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		if (status == 131 && !rayan)
		{
			ft_putendl_fd("Quit (core dumped)", 2);
			rayan++;
		}
	}
	rayan = 0;
	signal(SIGINT, & ctrlc);
	update_status_code(data, 0);
}
