/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:25:58 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/21 18:53:58 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*\*/
int	check_quote(const char *str)
{
	int	i;
	int	singleopen;
	int	doubleopen;

	i = -1;
	singleopen = 0;
	doubleopen = 0;
	while (str[++i])
	{
		if (str[i] == '"' && singleopen == 0 && doubleopen == 0)
			doubleopen = 1;
		else if (str[i] == '"' && singleopen == 0 && doubleopen == 1)
			doubleopen = 0;
		else if (str[i] == 39 && doubleopen == 0 && singleopen == 0)
			singleopen = 1;
		else if (str[i] == 39 && doubleopen == 1 && singleopen == 1)
			singleopen = 0;
		else if (str[i] == 39 && doubleopen == 0 && singleopen == 1)
			singleopen = 0;
	}
	if (singleopen == 1 || doubleopen == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static
int	exist_after(const char *str, int index, int c, int search)
{
	int	i;
	int	temp;

	i = index + 1;
	while (str[i])
	{
		temp = 0;
		while (ft_isspace(str[i]))
		{
			i++;
			temp++;
		}
		if (str[i] != c && str[i] != search)
			return (EXIT_SUCCESS);
		if (((str[i] == c && temp != 0) || str[i] == search) || (temp > 0 && c == search))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

#define SYNTAX_ERROR "bash: syntax error near unexpected token"
static int	check_chevron(const char *str, const char c)
{
	int	i;
	int	j;
	int	len;

	len = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (ft_isspace(str[i]))
			i++;
		while (str[i + j] == c)
		{
			if ((i + j == 0 && c == '|') || (c == '|' && exist_after(str, i + j, c, '|')))
				return (ft_putendl_fd("Syntax error", 2));
			if ((c == '>' && exist_after(str, i + j, c, '<'))
				|| (c == '<' && exist_after(str, i + j, c, '>')))
				return (ft_putendl_fd("Syntax error", 2));
			j++;
		}
		while (ft_isspace(str[i + j]))
			i++;
		if (j == 3)
			return (ft_printf("%s '%c'\n", SYNTAX_ERROR, c));
		else if (j >= 4)
			return (ft_printf("%s '%c%c'\n", SYNTAX_ERROR, c, c));
		if (!str[i + j] && j > 0)
		{
			if (c == '|')
				return (ft_printf("%s '%c'\n", SYNTAX_ERROR, c));
			return (ft_printf("%s 'newline'\n", SYNTAX_ERROR));
		}
		if (!str[i])
			break ;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_chevrons(const char *str)
{
	return (check_chevron(str, '<') > 0 || check_chevron(str, '>') > 0
		|| check_chevron(str, '|') > 0);
}

/*\*/