/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:52:31 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/17 07:27:06 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

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

static
void	pipe_redirection(t_data *data, const int index_pid)
{
	const int	lstcount = ft_lstcount(data -> cmd);

	if (index_pid != 0)
	{
		dup2(data -> prev_pipe, STDIN_FILENO);
		close(data -> prev_pipe);
	}
	if (index_pid != lstcount - 1)
		dup2(data -> pipes[1], STDOUT_FILENO);
	close(data -> pipes[1]);
	close(data -> pipes[0]);
}

static
void	is_child(t_data *data, t_cmd *ptr, int index_pid)
{
	is_heredoc(data, ptr);
	char *command = valid_command(ptr -> command, data -> path);

	if (!command)
	{
		if (ptr -> command)
			ft_printf("%s: command not found\n", ptr -> command);// exit code 127
		if (data -> pipes[0] != -1)
			close(data -> pipes[0]);
		if (data -> pipes[1] != -1)
			close(data -> pipes[1]);
	}
	else
	{
		pipe_redirection(data, index_pid);
		is_redirection(ptr);
		if (ft_strchr(ptr -> command, '/'))
			execve(ptr -> command, ptr -> args, data -> env);
		else
		{
			if (command)
			{
				
				execve(command, ptr -> args, data -> env);
				ft_memdel((void **)& command);
			}
		}
		ft_putendl_fd("Failed execve", 2);
	}
	free_shell(data);
	exit(EXIT_FAILURE);
}

static
void	is_father(t_data *data)
{
	if (data -> prev_pipe != -1)
		close(data -> prev_pipe);
	close(data -> pipes[1]);
	data -> prev_pipe = data -> pipes[0];
}

void	exec(const char *input, t_data *data)
{
	t_cmd		*ptr;
	int			size_path_env;
	int			index_pid;
	int			path_id;
	int			status;

	ptr = data -> cmd;
	size_path_env = 0;
	status = 0;
	index_pid = 0;
	while (ptr)
	{
		if (pipe(data -> pipes) < 0)
			return ;
		data -> pids[index_pid] = fork();
		if (data -> pids[index_pid] == -1)
		{
			if (data -> pipes[0] != -1)
				close(data -> pipes[0]);
			if (data -> pipes[1] != -1)
				close(data -> pipes[1]);
			free_shell(data);
			return ;
		}
		if (data -> pids[index_pid] == 0)
		{
			if (is_builtin(ptr, data) == EXIT_SUCCESS)
			{
				if (data -> pipes[0] != -1)
					close(data -> pipes[0]);
				if (data -> pipes[1] != -1)
					close(data -> pipes[1]);
				free_shell(data);
				exit(EXIT_SUCCESS);
			}
			is_child(data, ptr, index_pid);
		}
		if (data -> pids[index_pid] > 0)
			is_father(data);
		index_pid++;
		ptr = ptr -> next;
	}
	close(data -> pipes[0]);
	close(data -> pipes[1]);
	for (int i = 0; i < index_pid; i++)
		waitpid(data -> pids[i], &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	//printf("Return status is : %d\n", status);
}
