/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_booster.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 23:27:10 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/13 23:33:26 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**split_boost(t_data *data, char const *s)
{
	char	**res;
	size_t	len;

	if (!s)
		return (NULL);
	len = countword(s, sep);
	res = malloc(sizeof(char *) * (len + 1));
	// if (res)
	// 	wordfill(res, s, sep, len);
	return (res);
}

static int	count_nbword(t_data *data, char const *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if 
}