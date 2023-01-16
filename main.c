/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:47:36 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/16 17:32:34 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	const char	*input;
	t_data		data;
	char		**res;

	if (!env || !*env)
		return (0);
	ft_bzero(& data, sizeof(t_data));
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, & ctrlc);
	data . cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!data . cmd)
		return (EXIT_FAILURE);
	data . prev_pipe = -1;
	set_data(env, & data);
	// export(&data, "test=");
	while (1)
	{
		input = readline("Fumier$ ");
		if (!input)
		{
			free_shell(data);
			break ;	//exit code 130
		}
		if (*input && check_chevrons(input) == EXIT_SUCCESS)
		{
			add_history(input);
			if (check_quote(input) == EXIT_SUCCESS)
			{
				if (!data . cmd)
				{
					data . cmd = ft_calloc(sizeof(t_cmd), 1);
					if (!data . cmd)
						return (EXIT_FAILURE);
				}
				data . prev_pipe = -1;
				parse_input(input, data . cmd, & data);
				//print_cmd(data . cmd);
				//exec(input, & data, env);
			}
			else
				ft_putstr_fd("Syntax error\n", 2);
		}
		free_cmd(data . cmd);
		data . cmd = 0;
		ft_memdel((void **)& input);
	}
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
