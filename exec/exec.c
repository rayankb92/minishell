/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:52:31 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/18 20:22:24 by rferradi         ###   ########.fr       */
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

	if (index_pid != 0)
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

	tmp = 0;
	command = valid_command(ptr -> command, data -> path);
	is_heredoc(data, ptr);
	if (!command && ptr -> command)
		ft_printf("%s: command not found\n", ptr -> command, tmp += 1);// status code 127
	else
	{
		pipe_redirection(data, index_pid);
		is_redirection(ptr);
		if (ptr -> command)
		{
			if (ft_strchr(ptr -> command, '/'))
				execve(ptr -> command, ptr -> args, data -> env);
			else
				execve(command, ptr -> args, data -> env);
			ft_putendl_fd("Failed execve", 2);
		}
	}
	if (13 == errno && !tmp)
		ft_printf("%s: %s: Permission denied\n", ptr -> command, ptr -> args[1]); // status code 1
	if (1 == errno && !tmp)
		ft_printf("%s: %s: No such file or directory\n", ptr -> command, ptr -> args[1]); //status 1
	if (126 == errno && !tmp)
		ft_printf("%s: %s: Is a directory\n", ptr -> command, ptr -> args[1]);// status code 126
	close_fd(& data -> pipes);
	ft_memdel((void **)& command);
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
	int			index_pid;
	int			path_id;
	int			status;

	ptr = data -> cmd;
	status = 0;
	index_pid = 0;
	while (ptr)
	{
		if (is_builtin(ptr, data) == EXIT_FAILURE)
		{
			if (pipe(data -> pipes) < 0)
				return ;
			data -> pids[index_pid] = fork();
			if (data -> pids[index_pid] == -1)
			{
				close_fd(& data -> pipes);
				free_shell(data);
				exit(EXIT_FAILURE);
			}
			if (data -> pids[index_pid] == 0)
				is_child(data, ptr, index_pid);
			if (data -> pids[index_pid] > 0)
				is_father(data);
		}
		index_pid++;
		ptr = ptr -> next;
	}
	close_fd(& data -> pipes);
	for (int i = 0; i < index_pid; i++)
		waitpid(data -> pids[i], &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	//printf("Return status is : %d\n", status);
}
