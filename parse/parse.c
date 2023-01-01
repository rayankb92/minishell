/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:25:58 by rferradi          #+#    #+#             */
/*   Updated: 2022/12/31 16:53:51 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#define CHARSET "$<>| "
#define CHEVRON "<>"

// en gros quand une cote est mal fermer dans bash il va te print a la ligne
// >
// et il attend que tu ferme les cote
// nous on doit pas gerer ca on ecrit juste syntax error si y a heja

int	check_quote(char *str)
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
		printf("Syntax Error\n");
	return (1);
}

int	check_operateur(char *str)
{
	int	i;

	i = -1;
	if (ft_strnstr(str, "<>", -1))
		return (error_msg("Syntax error\n"));
	while (str[++i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			if (str[i + 1] == '<' || str[i + 1] == '>')
				i++;
			while ((str[++i]) && (str[i] == ' ' || str[i] == '\n'));
			if (!str[i])
				return (error_msg("Shellzer: syntax error near unexpected token `newline'\n"));
			i--;
		}
	}
	return (0);
}

// 