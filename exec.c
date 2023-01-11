/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:52:31 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/11 01:51:51 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

const char	**set_paths(char **paths, int *size)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = ft_strjoin(paths[++i] + 5, "/");
	if (!tmp)
		return (0);
	ft_memdel((void **)& paths[i]);
	paths[i] = tmp;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (0);
		ft_memdel((void **)& paths[i]);
		paths[i] = tmp;
	}
	*size = i;
	return ((const char **)paths);
}

const char	**env_paths_to_string(char **env, int *size)
{
	int		i;
	int		j;
	char	*tmp;
	char	**paths;

	i = -1;
	while (env[++i])
	{
		if (ft_strnstr(env[i], "PATH", 4))
		{
			paths = ft_split(env[i], ':');
			if (!paths)
				break ;
			return (set_paths(paths, size));
		}
	}
	return (0);
}

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

void	is_redirection(t_cmd *ptr)
{
	static const int	indexs[3] = {
		O_WRONLY | O_CREAT | O_TRUNC, 
		O_WRONLY | O_CREAT | O_APPEND,
		O_RDONLY // stdinfileno
	};
	int	fd;
	int	i;

	if (ptr -> sequence)
	{
		i = 0;
		while (i < ptr -> length_sequence)
		{
			// hard code
			if (ptr -> sequence[i] . redirect != ptr -> files[0] . redirect
				&& ptr -> sequence[i] . redirect != ptr -> files[1] . redirect
				&& ptr -> sequence[i] . redirect != ptr -> files[2] . redirect
				&& ptr -> sequence[i] . redirect != ptr -> files[3] . redirect)
			{
				fd = open(ptr -> sequence[i] . redirect, indexs[ptr -> sequence[i] . index_redirect - 1], 0644);
				if (fd < 0)
					ft_putendl_fd("Cannot open file", 2);
				close(fd);
			}
			i++;
		}
		// hard code
		int fdgreat = -1, fddgreat = -1, fdless = -1, fddless = -1;
		if (ptr -> files[0] . index_redirect != -1)
		{
			fdgreat = open(ptr -> files[0] . redirect, indexs[ptr -> files[0] . index_redirect - 1], 0644);
			if (fdgreat < 0)
				ft_putendl_fd("Cannot open file", 2);
			dup2(fdgreat, STDOUT_FILENO);
		}
		if (ptr -> files[1] . index_redirect != -1)
		{
			fddgreat = open(ptr -> files[1] . redirect, indexs[ptr -> files[1] . index_redirect - 1], 0644);
			if (fddgreat < 0)
				ft_putendl_fd("Cannot open file", 2);
			dup2(fddgreat, STDOUT_FILENO);
		}
		if (ptr -> files[2] . index_redirect != -1)
		{
			fdless = open(ptr -> files[2] . redirect, indexs[ptr -> files[2] . index_redirect - 1], 0644);
			if (fdless < 0)
				ft_putendl_fd("Cannot open file", 2);
			dup2(fdless, STDIN_FILENO);
		}
		if (ptr -> files[3] . index_redirect != -1)
		{
			fddless = open(ptr -> files[3] . redirect, indexs[ptr -> files[3] . index_redirect - 1], 0644);
			if (fddless < 0)
				ft_putendl_fd("Cannot open file", 2);
			dup2(fddless, STDIN_FILENO);

		}
		close(fdgreat);
		close(fddgreat);
		close(fdless);
		close(fddless);
	}
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
					ft_printf("%s: command not found\n", ptr -> command);
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
