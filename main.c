/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:47:36 by rferradi          #+#    #+#             */
/*   Updated: 2022/12/30 05:08:14 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>


int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	const char *str;
	while (1)
	{
		str = readline("Fumier> ");
		add_history(str);
		printf("commande = %s\n", str);
		check_quote((char *)str);
	}
}
