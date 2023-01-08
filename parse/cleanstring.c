/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanstring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 01:26:17 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/08 23:20:27 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*putspace_between_operateur(char *str);

char	**clean_string(char *str, t_data *data)
{
	char	**clean;
	char	*neg;
	char	*ope;

	neg = negative_chars(str, data);
	free(str);
	ope = putspace_between_operateur(neg);
	clean = split_quote(ope, ISSPACE);
	free(neg);
	positive_chars(clean);
	return (clean);
}

static int	count_newlen(t_data *data, char *str)
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
			{
				if ((str[i] == '$') && (str[i + 1]) && (is_variable(str[i + 1])))
				{
					i += get_varname_len(&str[i + 1]);
					len += get_varvalue_len(data, &str[i + 1]);
				}
				len++;
			}
			i++;
		}
		if ((str[i] == '$') && (str[i + 1]) && (is_variable(str[i + 1])))
		{
			len += get_varvalue_len(data, &str[i + 1]); 
			i += get_varname_len(&str[i + 1]);
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

int	add_value(char *new, char *str, t_data *data, int *j)
{
	int		i;
	char	*var;

	i = -1;
	var = find_var(data, str + 1);
	if (!var)
		return (get_varname_len(str + 1));
	while (var[++i])
	{
		new[*j] = var[i] * -1;
		*j += 1;
	}
	return (get_varname_len(str + 1));
}

int	add_value_nospace(char *new, char *str, t_data *data, int *j)
{
	int		i;
	char	*var;

	i = -1;
	var = find_var(data, str + 1);
	if (!var)
		return (get_varname_len(str + 1));
	var = ft_strtrim(var, ISSPACE);
	while (var[++i])
	{
		if (ft_isspace(var[i]))
		{
			while (var[i] && ft_isspace(var[i]))
				i++;
			new[*j] = -32;
			*j += 1;
			i--;
		}
		else
		{
			new[*j] = var[i] * -1;
			*j += 1;
		}
	}
	return (get_varname_len(str + 1));
}

int	count_ope(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (is_in_charset(str[i], "|<>") && !is_in_charset( str[i - 1], "|<>"))
			count += 2;
		i++;
	}
	return (i + count);
}

char	*putspace_between_operateur(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (count_ope(str) + 1));
	while (str[i])
	{
		if (str[i] > 0)
		{
			if (is_in_charset(str[i], "|<>"))
			{
					new[j++] = ' ';
				if ((ft_strncmp(str + i, ">>", 2) == 0 || ft_strncmp(str + i, "<<", 2) == 0) && str[i + 1])
					new[j++] = str[i++];
				if (str[i])
					new[j++] = str[i++];
				new[j++] = ' ';
			}
		}
		new[j++] = str[i++];
	}
	new[j] = 0;
	return (new);
}


char	*negative_chars(char *str, t_data *data)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char ) * (count_newlen(data, str) + 1));
	while (str[i])
	{
		if (str[i] == '"')
		{
			while (str[++i] && str[i] != '"')
			{
				if ((str[i] == '$') && (str[i + 1]) && (is_variable(str[i + 1])))
				{
					i += add_value(new, &str[i],  data, &j);
					if (str[i] == '|')
						new[j++] = ' ';
				}
				else
					new[j++] = (str[i] * -1);
			}
			i++;
		}
		else if (str[i] == '\'')
		{
			while (str[++i] && str[i] != '\'')
				new[j++] = (str[i] * -1);
			i++;
		}
		else if (str[i] == '$' && str[i + 1] && is_variable(str[i + 1]))
		{
			i += add_value_nospace(new, &str[i++],  data, &j);
		}
		else
			new[j++] = str[i++];
	}
	new[j] = 0;
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
