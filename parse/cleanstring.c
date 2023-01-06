/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanstring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 01:26:17 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/06 21:14:46 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**clean_string(char *str)
{
	char	**clean;
	char	*neg;

	neg = negative_chars(str);
	free(str);
	clean = split_quote(neg, "	 ");
	free(neg);
	positive_chars(clean);
	return (clean);
}

static int	count_newlen(char *str)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			while (str[++i] && str[i] != '"')
				len++;
			i++;
		}
		if (str[i] == '"')
		{
			while (str[++i] && str[i] != '"')
				len++;
			i++;
		}
		len++;
	}
	return (len);
}

char	*positive_char(char *str)
{
	int i = -1;

	while (str[++i])
	{
		if (str[i] < 0)
			ft_putchar(str[i] * -1);
		else
			ft_putchar(str[i]);
	}
	write(1, "\n", 1);
}

char	*negative_chars(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char ) * (ft_strlen(str) + 100));
	while (str[i])
	{
		if (str[i] == '"')
		{
			while (str[++i] && str[i] != '"')
				new[j++] = (str[i] * -1);
			i++;
		}
		else if (str[i] == '\'')
		{
			while (str[++i] && str[i] != '\'')
				new[j++] = (str[i] * -1);
			i++;
		}
		else
			new[j++] = str[i++];
	}
	new[j] = 0;
	ft_printf("%s\n", new);
	positive_char(new);
	return (new);
}

void	positive_chars(char **str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] < 0)
				str[i][j] = (str[i][j] * -1);
		}
	}
}
