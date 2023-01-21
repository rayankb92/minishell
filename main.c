/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:47:36 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/21 18:50:48 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static
void	quit(t_data *data)
{
	int	status;

	status = ft_atoi(get_key_from_tenv(data -> tenv, "?"));
	free_shell(data);
	rl_clear_history();
	ft_putendl_fd("exit", 2);
	exit(status);
}

// int list_dir(void);

// int main()
// {
// 	list_dir();
	
// 	return 0;
// }
void	copy_files(char *find, t_data *data);


int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	const char	*input;
	t_data		data = {0};

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, & ctrlc);
	if (!isatty(STDIN_FILENO))
		return (EXIT_FAILURE);
	while (1)
	{
		input = readline("Fumier$ ");
		if (!input)
			quit(& data);
		if (*input)
			add_history(input);
		if (*input && check_chevrons(input) == EXIT_SUCCESS)
		{
			if (check_quote(input) == EXIT_SUCCESS)
			{
				if (init_data(& data, env))
					return (EXIT_FAILURE);
				copy_files("lala", &data);
				data.expand = 1;
				parse_input(input, data . cmd, & data);
				data.herecopy = split_iscote((char *)input);
				//print_cmd(data.cmd);
				exec(& data);
				//free_shell(& data);
				free_heredoc(data . here_doc, data . len_here);
				data . here_doc = 0;
				data . len_here = 0;
				free_cmd(data . cmd);
				ft_arraydel(data . path);
				data . path = 0;
				ft_arraydel(data . herecopy);
				data . herecopy = 0;
				data . cmd = 0;
			}
			else
				ft_putstr_fd("Syntax error\n", 2);
		}
		else
			update_status_code(& data, 2);
		ft_memdel((void **)& input);
	}
	quit(& data);
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
