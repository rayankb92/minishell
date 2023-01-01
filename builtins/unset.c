/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 01:38:06 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/01 03:05:24 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	var_name_len(char *name)
{
	int	i;

	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	return (i);
}

int	unset(char **env, char *name)
{
	int	len;
	int	i;

	len = var_name_len(name);
	i = 0;
	while (env[++i])
	{
		if (ft_strncmp(name, env[i], len) == 0)
		{
			ft_printf("laa\n");
			// free(env[i]);
			// env[i] = env[++i];
			while (env[i] && env[i + 1])
			{
					env[i] = env[i + 1];
					i++;
			}
			env[i] = 0;
			break;
		}
	}
}

// rayan=okok
// J=wefwe
// moha=2efois