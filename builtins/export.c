/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:35:41 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/01 02:01:38 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	export(char **env, char *name, char *value)
{
	int	i;
	char	*export;
	int		len;

	i = 0;
	len = ft_strlen(name);
	export = ft_strjoin(ft_strjoin(name, "="), value);
	printf("valeur de export = %s\n\n\n", export);
	while (env[i])
	{
		if ((ft_strncmp(name, env[i], len) == 0) && (env[i][len] == '='))
		{
			env[i] = export;
			break;
		}
		else if (!env[i + 1])
		{
			env[i + 1] = export;
			env[i + 2] = 0;
			break;
		}
		i++;
	}
	printf("\n\n\n");
}