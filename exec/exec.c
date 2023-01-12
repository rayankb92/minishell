/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:52:31 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/12 00:12:45 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

int	valid_command(const char *command, const char **env)
{
	int			i;
	char	*joined;

	i = -1;
	joined = 0;
	while (command && env[++i])
	{
		if (ft_strchr(command, '/'))
			joined = ft_strdup(command);
		else
			joined = ft_strjoin(env[i], command);
		if (access(joined, X_OK) == 0)
		{
			ft_memdel((void **)& joined);
			return (i);
		}
		ft_memdel((void **)& joined);
	}
	return (-1);
}

void	exec(const char *input, t_cmd *cmd, char **env)
{
	t_cmd		*ptr;
	pid_t		pids[4096]; // test
	const char	**path_env;
	int			size_path_env;
	int			index_pid;
	int			path_id;
	int			status;
	ptr = cmd;
	path_env = env_paths_to_string(env, & size_path_env);
	int pipes[2]; // test   1 = write   0 = read
	index_pid = 0;
	int		prev_pipes = -1;
	status = 0;
	if (is_builtin(ptr) == EXIT_FAILURE)
	{
		while (ptr)
		{
			if (pipe(pipes) < 0)
				return ;
			pids[index_pid] = fork();
			if (pids[index_pid] == 0)
			{
				path_id = valid_command(ptr -> command, path_env);
				if (path_id == -1)
				{
					if (is_in_string(ptr -> command, "><") == EXIT_SUCCESS)
						is_redirection(ptr);
					else
						ft_printf("%s: command not found\n", ptr -> command);
				}
				else
				{
					//is_heredoc(ptr);
					is_redirection(ptr);
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
				}
				exit(EXIT_FAILURE);
				close(pipes[0]);
				close(pipes[1]);
			}
			else
			{
				if (prev_pipes != -1)
					close(prev_pipes);
				close(pipes[1]);
				prev_pipes = pipes[0];
			}
			index_pid++;
			ptr = ptr -> next;
			// if (ptr)
			// 	dup2(pipes[1], STDOUT_FILENO);
			// else
			// 	dup2(prev_pipes, STDIN_FILENO);
		}
		close(pipes[0]);
		close(pipes[1]);
		for (int i = 0; i < index_pid; i++)
			waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))//?
			status = WEXITSTATUS(status);//?
		//printf("Return status is : %d\n", status);
	}
}
