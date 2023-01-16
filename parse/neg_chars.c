/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neg_chars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:03:52 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/16 19:20:28 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_newlen(t_data *data, char *str)
{
	int	i;
	int	len;
	int	lenstr;

	i = -1;
	len = 0;
	lenstr = ft_strlen(str);
	while (++i < lenstr)
	{
		if (str[i] && str[i] == '"')
		{
			while (str[++i] && str[i] != '"')
			{
				if ((str[i] == '$') && (str[i + 1]) && (is_variable(str[i + 1])))
					i += add_varlen_(data, &str[i + 1], &len);
			
				len++;
			}
			i++;
		}
		else if ((i <= len) && (str[i] == '$') && (str[i + 1]) && (is_variable(str[i + 1])))
					i += add_varlen_(data, &str[i + 1], &len);
		len++;
	}
	return (len);
}

int	find_char(char c)
{
	if (ft_isspace(c))
		return (c * - 1);
	if (c == '|')
		return PIPE;
	else if (c == '>')
		return CHEVLEFT;
	else if (c == '<')
		return CHEVRIGHT;
	else
		return (c);
}

void	double_quote_check(char **dbl, int *i, int *j, t_data *data)
{
	char *str;
	char *new;

	str = dbl[0];
	new = dbl[1];

	if (str[*i + 1] == '"')
		new[(*j)++] = SLASHBACK;
	while (str[++(*i)] && str[*i] != '"')
	{
		if ((str[*i] == '$') && (str[*i + 1]) && (is_variable(str[*i + 1])))
			*i += add_value(new, &str[*i],  data, j);
		else
			new[(*j)++] = find_char(str[*i]);
	}
	(*i)++;
}

char	*negative_chars(char *str, t_data *data)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char ) * (count_newlen(data, str) + 1));
	if (!new || new == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"')
			double_quote_check((char *[2]){str, new}, &i, &j, data);
		else if (str[i] == '\'')
		{
			if (str[i + 1] == '\'')
				new[j++] = SLASHBACK;
			while (str[++i] && str[i] != '\'')
				new[j++] = find_char(str[i]);
			i++;
		}
		else if (str[i] == '$' && str[i + 1] && is_variable(str[i + 1]))
		{
			i += add_value_nospace(new, str + i,  data, &j);
			i++;
		}
		else
			new[j++] = str[i++];
	}
	new[j] = 0;
	return (new);
}
