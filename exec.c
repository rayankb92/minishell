/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:52:31 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/09 15:26:32 by jewancti         ###   ########.fr       */
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

	ptr = cmd;
	path_env = env_paths_to_string(env, & size_path_env);
	if (is_builtin(ptr) == EXIT_FAILURE)
	{
		while (ptr)
		{
			pids[index_pid] = fork();
			if (pids[index_pid] == 0)
			{
				path_id = valid_command(ptr -> command, path_env);
				if (path_id == -1)
					ft_printf("%s: command not found\n", ptr -> command);
				else
				{
					if (ptr -> command[0] == '/')
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
			}
			index_pid++;
			ptr = ptr -> next;
		}
		for (int i = 0; i < index_pid; i++)
			waitpid(pids[i], 0, 0);
	}
}
