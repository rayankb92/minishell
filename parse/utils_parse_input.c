/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:25:30 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/08 21:33:48 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		count_occurence(const char *str, const char c)
{
	size_t	i;
	int		occur;

	i = 0;
	occur = 0;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != '\0')
		{
			if (str[i + 1] == c)
				i++;
			occur++;
		}
		i++;
	}
	return (occur);
}

int		get_length_args(char **ptr)
{
	int	i;
	int	size;

	size = 1;
	i = 1;
	while (ptr[i])
	{
		while (ptr[i] && ptr[i][0] != '>' && ptr[i][0] != '<')
		{
			size++;
			i++;
		}
		if (ptr[i] && (ptr[i][0] == '>' || ptr[i][0] == '<'))
			i += 2;
	}
	return (size);
}

void	ft_realloc(char **line, const char *s1)
{
	char	*res;
	int		i;

	if (*line && **line)
	{
		i = 0;
		while ((*line)[i])
			i++;
		res = malloc(ft_strlen(s1) + i + 1);
		if (res)
		{
			ft_strcpy(res, *line);
			ft_strcpy(res + i, s1);
			free(*line);
			*line = res;
		}
		return ;
	}
	if (*line && !**line)
		free(*line);
	*line = ft_strdup(s1);
}

char	*array_to_string(char **array)
{
	char	*tostring;
	int		i;

	i = 0;
	tostring = 0;
	while (array[i])
	{
		if (array[i + 1] == 0)
			ft_realloc(& tostring, array[i]);
		else
			ft_realloc(& tostring, ft_strjoin(array[i], " "));
		i++;
	}
	return (tostring);
}
