/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:47:36 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/01 03:09:52 by rferradi         ###   ########.fr       */
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
	export(env, "rayan", "la valeur");
	// export(env, "JM", "ouaisc le J");
	export(env, "J", "wefwe");
	export(env, "rayan", "2eois");
	export(env, "moha", "2eois");
	unset(env, "LESS");
	unset(env, "LS_COLORS");
	ft_displaydouble(env);
	while (1)
	{
		str = readline("Fumier >$ ");
		if (ft_strncmp(str, "exit", 4) == 0)
			break;
		if (ft_strncmp("env", str))
			ft_displaydouble(env);
		if (ft_strncmp("export", str, 6) == 0)
			export(env,)
		add_history(str);
		printf("commande = %s\n", str);
		check_quote((char *)str); // tres propre gere tout les cas cote non fermer
		check_operateur((char *)str);//pas propre du tout gere qlq cas
	}
	return (1);
}
