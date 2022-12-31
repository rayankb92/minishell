/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:47:36 by rferradi          #+#    #+#             */
/*   Updated: 2022/12/31 12:46:25 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
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
		printf("commande = %s\n", str);
		check_quote((char *)str); // tres propre gere tout les cas cote non fermer
		check_operateur((char *)str);//pas propre du tout gere qlq cas
	}
	return (1);
}
