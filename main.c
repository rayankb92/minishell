/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:47:36 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/05 19:13:55 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	const char	*str;
	t_data		data;
	t_cmd		*cmd;

	if (!env || !*env)
		return (0);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, & ctrlc);
	cmd = calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (EXIT_FAILURE);
	cmd -> next = 0; // !!
	set_data(env, & data);
	while (1)
	{
		str = readline("Fumier$ ");
		if (!str)
			break ;
		add_history(str);
		if (!check_chevrons(str) && check_quote(str) == 1)
		{
			is_exit(str);
			parse_input(str, cmd);
			print_cmd(cmd);
			exec(cmd);
		}
	}
	// rayan
	//while (1)
	//{
	//	str = readline("Fumier >$ ");
	//	if (check_quote(str))
	//	{

	//		split = split_cmd(str, "| ");
	//		// expand(split, &data);
	//		ft_printf("laa\n");
	//		// print_cmd(data.cmd);
	//		handle_quote((char *)str, &data);
	//		// ft_printf("expand = %s\n", data.cmd->args[0]);
	//		if (ft_strncmp((char*)str, "exit", 4) == 0)
	//			break;
	//		if (ft_strncmp("env", str, 3) == 0)
	//			ft_displaydouble(env);
	//		// if (ft_strncmp("export", str, 6) == 0)
	//		// 	export(env,)
	//		check_chevrons(str);	
	//	}
	//		add_history(str);
	//}
	return (EXIT_SUCCESS);
}
