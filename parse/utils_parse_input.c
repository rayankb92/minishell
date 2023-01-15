/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:25:30 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/14 18:01:41 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		count_occurence(const char *str, const char c)
{
	size_t	i;
	size_t	occur;
	size_t	size;

	i = 0;
	occur = 0;
	size = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != '\0')
		{
			if (str[i + 1] == c)
				i++;
			occur++;
		}
		i++;
		if (i >= size)
			break ;
	}
	return (occur);
}

static
int	get_size(char **ptr)
{
	int	i;

	i = -1;
	while (ptr[++i])
		;
	return i;
}

int		get_length_args(char **ptr)
{
	int	i;
	int	length;
	int	size;

	size = 1;
	i = 1;
	length = get_size(ptr);
	while (ptr[i])
	{
		while (ptr[i])
		{
			if (ptr[i][1] == 0 && (ptr[i][0] == '>' || ptr[i][0] == '<'))
				break ;
			if (ptr[i][1] != 0
				&& ((ptr[i][0] == '>' && ptr[i][1] == '<') || (ptr[i][0] == '<' && ptr[i][1] == '<'))
				&& ptr[i][2] == 0)
				break ;
			size++;
			i++;
		}
		if (ptr[i] && (ptr[i][0] == '>' || ptr[i][0] == '<'))
			i += 2;
		if (i >= length)
			break ;
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
		{
			char *tmp = ft_strjoin(array[i], " ");
			ft_realloc(& tostring, tmp);
			ft_memdel((void **)& tmp);
		}
		i++;
	}
	return (tostring);
}
