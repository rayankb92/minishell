/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:47:36 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/08 15:59:05 by jewancti         ###   ########.fr       */
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
	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (EXIT_FAILURE);
	cmd -> next = 0;
	set_data(env, & data);
	//parse_input("ls -la file_ls > outfile -R << here_doc > to_here -opt | cmd", cmd);
	//print_cmd(cmd);
	//exit(0);
	while (1)
	{
		str = readline("Fumier$ ");
		if (!str)
			break ;
		add_history(str);
		if (*str && check_chevrons(str) == EXIT_SUCCESS)
		{
			if (check_quote(str) == EXIT_SUCCESS)
			{
				parse_input(str, cmd);
				print_cmd(cmd);
				//exec(cmd);
				ft_memset(cmd, 0, sizeof(t_cmd));
				ft_memset(cmd -> sequence, 0, sizeof(t_sequence) * cmd -> length_sequence);
				char **res = clean_string((char *)str);
				ft_displaydouble(res);
			}
			else
				ft_putstr_fd("Syntax error\n", 2);
		}
	}
	return (EXIT_SUCCESS);
}
	
//______________________________________________________________
//| echo "salut" ""'"'"mec" "" [echo] [salut] [] ["] [mec] []	|
//| echo "salut" '"'mec       "" [echo] [salut] ["mec]		|
//| salut "mec													|
//|_____________________________________________________________|

// si un simple quote ouvert on prend tout comme string/commande/arg jusqu'a trouver la la prochaine quote fermante


// ____________________________________
// [echo] [salut] ["'mec] 				|
// 										|
// Fumier >$ echo "salut" '"'m'e'c		|
// must do > [echo] [salut] ["'mec] 
// _____________________________________|

// _________________________________________
// [echo] [salut] ["'m'e'c] 				|
// 											|
// Fumier >$ echo "salut" '"'m'e'c			|
// must do > [echo] [salut] ["mec]
// _________________________________________|	