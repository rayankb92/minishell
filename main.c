/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:47:36 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/03 23:17:37 by rferradi         ###   ########.fr       */
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
		split = split_cmd(str, "| ");
		expand(split, &data);
		print_cmd(data.cmd);
		ft_printf("expand = %s\n", data.cmd->args[0]);
		if (ft_strncmp(str, "exit", 4) == 0)
			break;
		if (ft_strncmp("env", str, 3) == 0)
			ft_displaydouble(env);
		// if (ft_strncmp("export", str, 6) == 0)
		// 	export(env,)
		add_history(str);
		check_quote(str); // tres propre gere tout les cas cote non fermer
		check_chevrons(str);	
	}
	return (1);
}
