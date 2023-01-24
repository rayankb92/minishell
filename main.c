/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:47:36 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/24 14:58:28 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_data	*starton(void)
{
	static t_data data = {0};

	return (&data);
}

static
void	quit(short status, t_data *data)
{
	free_shell(data);
	rl_clear_history();
	ft_putendl_fd("exit", 2);
	exit(status);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	const char	*input;
	short		status;
	t_data		*data;

	status = 0;
	data = starton();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, & ctrlc);
	if (!isatty(STDIN_FILENO))
	 	return (EXIT_FAILURE);
	while (1)
	{
		input = readline("Fumier$ ");
		if (!input)
			quit(status, data);
		if (*input)
			add_history(input);
		if (*input && check_chevrons(input) == EXIT_SUCCESS)
		{
			if (check_quote(input) == EXIT_SUCCESS)
			{
				if (init_data( data, env))
					return (EXIT_FAILURE);
				//copy_files("lala", &data);
				data -> expand = 1;
				parse_input(input, data -> cmd, data);
				data -> herecopy = split_iscote((char *)input);
				print_cmd(data->cmd);
				exec(data);
				//free_shell(data);
				status = ft_atoi(get_key_from_tenv(data -> tenv, "?"));
				free_heredoc(data -> here_doc, data -> len_here);
				data -> here_doc = 0;
				data -> len_here = 0;
				free_cmd(data -> cmd);
				ft_arraydel(data -> path);
				data -> path = 0;
				ft_arraydel(data -> herecopy);
				data -> herecopy = 0;
				data -> cmd = 0;
			}
			else
				ft_putstr_fd("Syntax error\n", 2);
		}
		else
		{
			update_status_code(data, 2);
			free_shell(data);
		}
		ft_memdel((void **)& input);
	}
	quit(status, data);
}
