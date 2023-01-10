/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:47:36 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/10 02:26:05 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	const char	*input;
	t_data		data;
	t_cmd		*cmd;
	char **res;

	if (!env || !*env)
		return (0);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, & ctrlc);
	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (EXIT_FAILURE);
	cmd -> next = 0;
	set_data(env, & data);
	while (1)
	{
		input = readline("Fumier$ ");
		if (!input)
			break ;
		add_history(input);
		if (*input && check_chevrons(input) == EXIT_SUCCESS)
		{
			if (check_quote(input) == EXIT_SUCCESS)
			{
				parse_input(input, cmd, & data);
				exec(input, cmd, env);
				ft_bzero(cmd, sizeof(t_cmd));
				ft_bzero(cmd -> sequence, sizeof(t_sequence) * cmd -> length_sequence);
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