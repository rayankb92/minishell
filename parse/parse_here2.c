/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 01:23:23 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/23 05:13:26 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#define ISSEP "\t\v\n\r\f <>|"
#define ISSEPP "\t\v\n\r\f <>|\"'"

void	countlen2(int *i, char *str, int *word)
{
	char	quote;

	while (ft_isspace(str[*i]))
		(*i)++;
	if (str[*i])
		(*word)++;
	if (str[*i] == '"' || str[*i] == '\'')
	{
		quote = str[(*i)++];
		while (str[*i] && str[*i] != quote)
			(*i)++;
		(*i)++;
	}
	else if (str[*i] && is_in_charset(str[*i], "|><"))
	{
		(*i)++;
		if (str[*i] && str[*i - 1] == str[*i])
			(*i)++;
	}
	else
		while (str[*i] && !is_in_charset(str[*i], ISSEPP))
			(*i)++;
}

int	countlen(char *str)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	if (!str)
		return (0);
	while (str[i])
		countlen2(&i, str, &word);
	return (word);
}

int	lenword(char *str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i + j] == '"' || str[i + j] == '\'')
	{
		quote = str[i + j++];
		while (str[i + j] && str[i + j] != quote)
			j++;
		j++;
	}
	else if (!is_in_charset(str[i + j], ISSEP))
	{
		while (!is_in_charset(str[i + j], ISSEP))
			j++;
	}
	else
		while (str[i + j] && is_in_charset(str[i + j], "<>|"))
			j++;
	return (j);
}
