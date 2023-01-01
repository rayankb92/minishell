/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:47:36 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/01 11:42:26 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	const char	*str;

	if (!env || !*env)
		return (0);
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
