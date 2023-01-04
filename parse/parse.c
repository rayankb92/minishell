/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:25:58 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/04 20:53:03 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#define CHARSET "$<>| "
#define CHEVRON "<>"

// en gros quand une cote est mal fermer dans bash il va te print a la ligne
// >
// et il attend que tu ferme les cote
// nous on doit pas gerer ca on ecrit juste syntax error si y a heja

int	check_quote(const char *str)
{
	int	i;

	i = -1;
	int singleopen = 0;
	int	doubleopen = 0;
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
		return printf("Syntax Error\n");
	return (1);
}
// a modifier: OK SI PIPE AVANT		
int	check_chevron(const char *str, const char c)
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
			j++;
		while (ft_isspace(str[i + j]))
			i++;
		if (j == 3)
			return (ft_printf("bash: syntax error near unexpected token '%c'\n", c));
		else if (j >= 4)
			return (ft_printf("bash: syntax error near unexpected token '%c%c'\n", c, c));
		if (!str[i + j] && j > 0)
			return (ft_printf("bash: syntax error near unexpected token 'newline'\n"));
		i++;
	}
	return (0);
}
// pas fini, gere pas tous les cas
int	check_chevrons(const char *str)
{
	int ret = check_chevron(str, '<');
	int ret2 = check_chevron(str, '>');
	return (ret > 0 || ret2 > 0);
}

// int	parse_cmd(t_data *data)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (ft_isspace(data->entry[i]) || !is_in_charset(data->entry[i], CHARSET))
// 		i++;
// 	while (!ft_isspace(data->entry[i]) || is_in_charset(data->entry[i], CHARSET))
// 		j++;
// 	data->cmd->args = ft_split(ft_substr(data->entry, i, (i + j)), ' ');
// 	return (1);
// }