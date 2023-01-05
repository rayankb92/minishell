/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:47:36 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/05 05:48:46 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// static	t_data	*get_data()
// {
// 	static	t_data	*
// }

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	ft_printf("la commande est : ");
	while(cmd->args[i])
		ft_printf("[%s] ", cmd->args[i++]);
	ft_printf("\n");
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	const char	*str;
	t_data	data;
	char **split;

	if (!env || !*env)
		return (0);
	set_data(env, &data);
	export(&data, "rayan", "Je suis la valeur de rayan");
	// ft_displaydouble(split);
	while (1)
	{
		str = readline("Fumier >$ ");
		if (check_quote(str))
		{

			split = split_cmd(str, "| ");
			// expand(split, &data);
			ft_printf("laa\n");
			// print_cmd(data.cmd);
			handle_quote((char *)str, &data);
			// ft_printf("expand = %s\n", data.cmd->args[0]);
			if (ft_strncmp((char*)str, "exit", 4) == 0)
				break;
			if (ft_strncmp("env", str, 3) == 0)
				ft_displaydouble(env);
			// if (ft_strncmp("export", str, 6) == 0)
			// 	export(env,)
			check_chevrons(str);	
		}
			add_history(str);
	}
	return (1);
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