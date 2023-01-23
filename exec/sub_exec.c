/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:16:58 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/23 00:39:44 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

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
	//close_fd(& data -> pipes);
	close(data-> pipes[0]);
	close(data-> pipes[1]);
}

static
int	start_command(t_data *data, t_cmd *ptr, char *command, int index_pid)
{
	pipe_redirection(data, index_pid);
	is_redirection(data, ptr);
	if (is_builtin(ptr) == EXIT_SUCCESS)
	{
		do_builtin(ptr, data);
		return (EXIT_SUCCESS);
	}
	if (ptr -> command && ptr -> command[0])
	{
		if (ft_strchr(ptr -> command, '/'))
			execve(command , ptr->args, data -> env);
		else
			execve(command, ptr -> args, data -> env);
	}
	close(data -> pipes[0]);
	close(data -> pipes[1]);
	return (EXIT_FAILURE);
}

void	is_child(t_data *data, t_cmd *ptr, int index_pid)
{
	char	*command;

	signal(SIGINT, & ctrlc);
	signal(SIGQUIT, & reactiv);
	command = valid_command(ptr -> command, data -> path);
	if (ptr -> command && is_builtin(ptr) && ((!command && !ft_strchr(ptr -> command, '/'))
		|| (ptr -> command[0] == '\0')))
	{
		update_status_code(data, 127);
		ft_printf("%s: command not found\n", ptr -> command);
	}
	else
	{
		if (start_command(data, ptr, command, index_pid) == EXIT_FAILURE)
		{
			if (13 == errno)
				ft_printf("%s: %s: Permission denied\n", ptr -> command, ptr -> args[1]); // status code 1
			else
				ft_printf("%s: %s: No such file or directory\n", ptr -> command, ptr -> args[1]); //status 1
		}
	}
	ft_memdel((void **)& command);
	free_shell(data);
	close(data -> pipes[0]);
	close(data -> pipes[1]);
	exit(data -> signal);
}

void	is_father(t_data *data, int index_pid)
{
	if (data -> pids[index_pid] > 0)
	{
		ft_printf("FD 0: %d| FD1 %d | PREV%d\n", data -> pipes[0], data -> pipes[1], data -> prev_pipe);
		close(data -> pipes[1]);
		if (data -> prev_pipe != -1)
			close(data -> prev_pipe);
		data -> prev_pipe = data -> pipes[0];
		signal(SIGQUIT, SIG_IGN);
	}
}
