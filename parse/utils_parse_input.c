/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:25:30 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/06 16:25:46 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*trim_all(const char *s, int size)
{
	char	*res;
	int		index;
	int		i;

	res = malloc(size + 1);
	if (!res)
		return (0);
	i = 0;
	index = 0;
	while (s[i] && index < size)
	{
		while (s[i] && index < size && s[i] != ' ')
			res[index++] = s[i++];

		if (index < size && s[i] == ' ')
		{
			while (s[i] && index < size && s[i] == ' ')
				i++;
			if (s[i] != '\0')
				res[index++] = ' ';
		}
	}
	res[index] = '\0';
	return (res);
}

char	*remove_space(const char *s, const int size)
{
	char	*res;
	int		i;
	int		length;
	int		temp;

	length = 0;
	temp = 0;
	i = 0;
	while (s[i] && i < size)
	{
		while (s[i] && i < size && s[i] != ' ')
		{
			length++;
			i++;
		}

		if (i < size && s[i] == ' ')
		{
			length++;
			while (s[i] && i < size && s[i] == ' ')
				i++;
			if (s[i] == '\0' || i == size - 1)
				length--;
		}
	}
	return (trim_all(s, length));
}
