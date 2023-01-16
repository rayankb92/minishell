/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanstring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 01:26:17 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/16 17:12:18 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		*putspace_between_operateur(char *str);
int			find_char(char c);
void		_display_pos(char *str);

char	**clean_string(char *str, t_data *data)
{
	char	**clean;
	char	*neg;
	char	*ope;

	neg = negative_chars(str, data);
	if (!neg)
		return (NULL);
	ope = putspace_between_operateur(neg);
	if (!ope)
	{
		ft_memdel((void **)& neg);
		return (NULL);
	}
	ft_memdel((void **)& neg);
	clean = split_quote(ope, ISSPACE);
	ft_memdel((void **)& ope);
	positive_chars(clean);
	return (clean);
}

int	add_varlen_(t_data *data, char *str, int *len)
{
	*len += get_varvalue_len(data, str);
	return (get_varname_len(str));
}

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
				// ft_printf("BEFORE I = %i\n", i);
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
				// ft_printf("AFTER I = %i\n", i);
		len++;
		// if (!str[i])
		// 	break;
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
		if (ft_isspace(var[i]))
			new[*j] = var[i] * -1;
		else if (str[i] == '|')
			new[*j] = 'K';
		else
			new[*j] = var[i];
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
			new[(*j)++] = ' ';
			i--;
		}
		else
		{
			new[*j] = find_char(var[i]);
			*j += 1;
		}
	}
	return (get_varname_len(str + 1));
}

// ➜  minishellgood git:(main) ✗ export a="> out"
// ➜  minishellgood git:(main) ✗ export b=">out" 

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
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] > 0 && is_in_charset(str[i], "|<>"))
		{
			new[j++] = ' ';
			if ((ft_strncmp(str + i, ">>", 2) == 0 || ft_strncmp(str + i, "<<", 2) == 0) && str[i + 1])
				new[j++] = str[i++];
			if (str[i])
				new[j++] = str[i++];
			new[j++] = ' ';
		}
		new[j++] = str[i++];
	}
	new[j] = 0;
	return (new);
}

// echo opppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp-R okokp  o eh

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
	ft_printf("count len = %i\n", (count_newlen(data, str)));
	new = malloc(sizeof(char ) * (200));
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
			{
				ft_printf("STR[%i] = '%c'\n", i, str[i]);
				new[j++] = find_char(str[i]);
			}
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
	ft_printf("\n%s\n", new);
	_display_pos(new);
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
			if (str[i][j] < -5)
				str[i][j] = (str[i][j] * -1);
		}
	}
}

// utils pour debug

void	_display_pos(char *str)
{
	int i = -1;
	while (str[++i])
	{
		if (str[i] < -5)
			ft_putchar(str[i] * -1);
		else
			ft_putchar(str[i]);
	}
	ft_putchar('\n');
}

// copy
// char	*negative_chars(char *str, t_data *data)
// {
	// int		i;
	// int		j;
	// char	*new;
// 
	// i = 0;
	// j = 0;
	// new = malloc(sizeof(char ) * (count_newlen(data, str) + 1));
	// if (!new || new == NULL)
		// return (NULL);
	// while (str[i])
	// {
		// if (str[i] == '"')
		// {
			// double_quote_check((char *[2]){str, new}, &i, &j, data);
			// if (str[i + 1] == '"')
			// 	new[j++] = SLASHBACK;
			// while (str[++i] && str[i] != '"')
			// {
			// 	if ((str[i] == '$') && (str[i + 1]) && (is_variable(str[i + 1])))
			// 		i += add_value(new, &str[i],  data, &j);
			// 	else
			// 		new[j++] = find_char(str[i]);
			// }
			// i++;
		// }
		// else if (str[i] == '\'')
		// {
			// if (str[i + 1] == '\'')
				// new[j++] = SLASHBACK;
			// while (str[++i] && str[i] != '\'')
				// new[j++] = find_char(str[i++]);
			// i++;
		// }
		// else if (str[i] == '$' && str[i + 1] && is_variable(str[i + 1]))
			// i += add_value_nospace(new, &str[i++],  data, &j);
		// else
			// new[j++] = str[i++];
	// }
	// new[j] = 0;
	// ft_printf("NEG = %s\n", new);
	// ft_printf("POS = ");
	// _display_pos(new);
	// ft_printf("\n");
	// return (new);
// }