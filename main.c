/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:47:36 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/02 11:53:10 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	const char	*str;
	t_data	data;

	if (!env || !*env)
		return (0);
	set_data(env, &data);
	export(&data, "rayan", "valeur");
	while (1)
	{
		str = readline("Fumier >$ ");
		if (ft_strncmp(str, "exit", 4) == 0)
			break;
		add_history(str);
		check_quote(str); // tres propre gere tout les cas cote non fermer
		check_chevrons(str);	
	}
	return (1);
}
