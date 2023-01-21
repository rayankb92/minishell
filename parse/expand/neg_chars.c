/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neg_chars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:03:52 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/21 18:52:28 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

static void	count_newlen2(char *s, int *i, int *len, t_data *data)
{
	while (s[++(*i)] && s[(*i)] != '"')
	{
		if ((s[*i] == '$') && (s[*i + 1]) && (is_variable(s[*i + 1])))
			*i += add_varlen_(data, &s[*i + 1], len);
		(*len)++;
	}
	(*i)++;
}

static int	count_newlen(t_data *data, char *s)
{
	int	i;
	int	len;
	int	lenstr;

	i = -1;
	len = 0;
	lenstr = ft_strlen(s);
	while (++i < lenstr)
	{
		if (s[i] && s[i] == '"')
			count_newlen2(s, &i, &len, data);
		else if (s[i] == '\'')
		{
			len++;
			while (s[++i] != '\'' && s[i])
				len++;
			i++;
		}
		else if ((i <= len) && data->expand && (s[i] == '$') && (s[i + 1])
			&& (is_variable(s[i + 1])))
			i += add_varlen_(data, &s[i + 1], &len);
		len++;
	}
	return (len);
}

int	find_char(char c)
{
	if (ft_isspace(c))
		return (c * -1);
	if (c == '|')
		return (PIPE);
	else if (c == '>')
		return (CHEVLEFT);
	else if (c == '<')
		return (CHEVRIGHT);
	else
		return (c);
}

static void	double_quote_check(char **dbl, int *i, int *j, t_data *data)
{
	char	*str;
	char	*new;

	str = dbl[0];
	new = dbl[1];
	if (str[*i + 1] == '"')
		new[(*j)++] = SLASHBACK;
	while (str[++(*i)] && str[*i] != '"')
	{
		if (data->expand && (str[*i] == '$') && (str[*i + 1])
			&& (is_variable(str[*i + 1])))
			*i += add_value(new, &str[*i], data, j);
		else
			new[(*j)++] = find_char(str[*i]);
	}
	(*i)++;
}

static void	simple_quote_check(char *str, char *new, int *j, int *i)
{
	if (str[*i + 1] == '\'' && str[*i + 2] && is_in_charset(str[*i + 2],
			ISSPACE))
		new[(*j)++] = SLASHBACK;
	else
		while (str[++(*i)] && str[*i] != '\'')
			new[(*j)++] = find_char(str[*i]);
	(*i)++;
}

char	*negative_chars(char *str, t_data *data)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (count_newlen(data, str) + 2));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"')
			double_quote_check((char *[2]){str, new}, &i, &j, data);
		else if (str[i] == '\'')
			simple_quote_check(str, new, &j, &i);
		else if (data->expand && str[i] == '$' && str[i + 1]
			&& is_variable(str[i + 1]))
			i += add_value_nospace(new, str + i, data, &j) + 1;
		else
			new[j++] = str[i++];
	}
	new[j] = 0;
	return (new);
}
