/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:52:31 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/16 05:01:39 by jewancti         ###   ########.fr       */
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
void	is_child(t_data *data, t_cmd *ptr, int index_pid, const char **path_env, char **env)
{
	int	path_id = valid_command(ptr -> command, path_env);

	is_redirection(ptr);
	if (path_id == -1)
	{
		if (ptr -> command)
			ft_printf("%s: command not found\n", ptr -> command);// exit code 127
	}
	else
	{
		pipe_redirection(data, index_pid);
		if (ft_strchr(ptr -> command, '/'))
			execve(ptr -> command, ptr -> args, env);
		else
		{
			char *tmpcmd = ft_strjoin(path_env[path_id], ptr -> command);
			if (tmpcmd)
			{
				execve(tmpcmd, ptr -> args, env);
				ft_memdel((void **)& tmpcmd);
			}
		}
		ft_putendl_fd("Failed execve", 2);
	}
	exit(EXIT_FAILURE);
}

static
void	is_father(t_data *data)
{
	//printf("%i|%i|%i\n", data -> pipes[0],data -> pipes[1],data -> prev_pipe);
	if (data -> prev_pipe != -1)
		close(data -> prev_pipe);
	close(data -> pipes[1]);
	data -> prev_pipe = data -> pipes[0];
}

void	exec(const char *input, t_data *data, char **env)
{
	t_cmd		*ptr;
	const char	**path_env;
	int			size_path_env;
	int			index_pid;
	int			path_id;
	int			status;

	ptr = data -> cmd;
	size_path_env = 0;
	path_env = env_paths_to_string(env, & size_path_env);
	status = 0;
	index_pid = 0;
	while (ptr)
	{
		if (pipe(data -> pipes) < 0)
			return ;
		data -> pids[index_pid] = fork();
		if (data -> pids[index_pid] == -1)
			return ;
		if (data -> pids[index_pid] == 0)
		{
			if (is_builtin(ptr, data) == EXIT_SUCCESS)
				exit(EXIT_SUCCESS);
			is_child(data, ptr, index_pid, path_env, env);
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
	ft_arraydel((char **)path_env);
	//printf("Return status is : %d\n", status);
}
