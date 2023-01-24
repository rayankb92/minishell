/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:16:58 by jewancti          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/01/24 18:18:23 by rferradi         ###   ########.fr       */
=======
/*   Updated: 2023/01/24 17:49:39 by jewancti         ###   ########.fr       */
>>>>>>> refs/remotes/origin/main
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

static
void	printenv(t_env *env)
{
	t_env	*temp;

	temp = env;
	if (temp)
		temp = temp -> next;
	while (temp)
	{
		if (temp -> key && temp -> value && temp->value[0])
		{
			ft_putstr(temp -> key);
			ft_putchar('=');
			ft_putendl(temp -> value);
		}
		else if (temp -> key && temp -> equal == 0)
		{
			ft_putstr(temp -> key);
			ft_putendl("=");
		}
		temp = temp -> next;
	}
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
	close(data -> pipes[0]);
	close(data -> pipes[1]);
	//close_fd(& data -> pipes);
}

static
int	start_command(t_data *data, t_cmd *ptr, char *command, int index_pid)
{
	pipe_redirection(data, index_pid);
	is_redirection(data, ptr);
	if (is_builtin(ptr) == EXIT_SUCCESS)
	{
		do_builtin(ptr, data, data -> pipes[1]);
		return (EXIT_SUCCESS);
	}
	if (ptr -> command && ptr -> command[0])
	{
		if (ft_strchr(ptr -> command, '/'))
			execve(ptr -> command, ptr -> args, data -> env);
		else
			execve(command, ptr -> args, data -> env);
		if (errno == 13 && access(ptr -> command, X_OK | R_OK) != -1)
			ft_printf("%s: Permission denied\n", ptr -> command);
		data -> signal = 127;
	}
	return (EXIT_FAILURE);
}

void	is_child(t_data *data, t_cmd *ptr, int index_pid)
{
	char	*command;

	signal(SIGINT, & ctrlc);
	signal(SIGQUIT, & reactiv);
	command = valid_command(ptr -> command, data -> path);
	if (ptr -> command && is_builtin(ptr)
		&& ((!command && !ft_strchr(ptr -> command, '/'))
			|| (ptr -> command[0] == '\0')))
	{
		update_status_code(data, 127);
		if (ptr->command[0] != VARVIDE)
			ft_printf("%s: command not found\n", ptr -> command);
	}
	else
		start_command(data, ptr, command, index_pid);
	ft_memdel((void **)& command);
	close(data -> pipes[0]);
	close(data -> pipes[1]);
	//close_fd(& data -> pipes);
	free_shell(data);
	exit(data -> signal);
}

void	is_father(t_data *data, int index_pid)
{
	if (data -> pids[index_pid] > 0)
	{
		ft_printf("%d|%d|%d\n", data -> pipes[0],
			data -> pipes[1], data -> prev_pipe);
		close(data -> pipes[1]);
		if (data -> prev_pipe != -1)
			close(data -> prev_pipe);
		data -> prev_pipe = data -> pipes[0];
		signal(SIGQUIT, SIG_IGN);
	}
}
