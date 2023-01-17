/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:47:36 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/17 07:49:53 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	const char	*input;
	t_data		data = {0};
	char		**res;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, & ctrlc);
	while (1)
	{
		input = readline("Fumier$ ");
		if (!input)
		{
			free_shell(& data);
			break ;	//exit code 130
		}
		if (*input && check_chevrons(input) == EXIT_SUCCESS)
		{
			add_history(input);
			if (check_quote(input) == EXIT_SUCCESS)
			{
				if (init_data(& data, env))
					return (EXIT_FAILURE);
				//display_env(data . tenv);
				//ft_displaydouble(data . env);
				parse_input(input, data . cmd, & data);
				//print_cmd(data . cmd);
				exec(input, & data);
				free_shell(& data);
			}
			else
				ft_putstr_fd("Syntax error\n", 2);
		}
		ft_memdel((void **)& input);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}



//export a=">out"
//bash $a =
//bash: >out: No such file or directory

//export a=">out" = impossible
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

//jewancti@e2r7p15:~/Desktop/minishell$ export ab="doihoihf>
//> ^C
//jewancti@e2r7p15:~/Desktop/minishell$ export ab="doihoihf>erge
//> ^C
//jewancti@e2r7p15:~/Desktop/minishell$ export ab=doihoihf>erge
//jewancti@e2r7p15:~/Desktop/minishell$ echo $ab
//doihoihf
//jewancti@e2r7p15:~/Desktop/minishell$ 
