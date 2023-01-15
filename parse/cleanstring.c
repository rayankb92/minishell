/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanstring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 01:26:17 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/15 01:25:53 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*putspace_between_operateur(char *str);
int		interpret_ope(char *str, t_data *data, char *new, int *j);

int	interpret_ope2(char *str, t_data *data, char *new, int *j)
{
	int	i;
	char quote;

	i = 0;
	quote = '"';
	if (ft_strncmp(str, "|", 1) == 0 || ft_strncmp(str, "|", 1) == 0)
	{
		new[(*j)++] = PIPE;
		return (1);
	}
	else if (ft_strncmp(str, ">", 1) == 0 || ft_strncmp(str, ">", 1) == 0)
	{
		new[*j] = CHEVRIGHT;
		(*j)++;
		return (1);
	}
	else if (ft_strncmp(str, "<", 1) == 0 || ft_strncmp(str, "<", 1) == 0)
	{
		new[*j] = CHEVLEFT;
		(*j)++;
		return (2);
	}
	else if (ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, ">>", 2) == 0)
	{
		new[(*j)++] = CHEVRIGHTD;
		new[(*j)++] = CHEVRIGHTD;
		return (2);
	}
	else if (ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, "<<", 2) == 0)
	{
		new[(*j)++] = CHEVLEFTD;
		new[(*j)++] = CHEVLEFTD;
		return (2);
	}
	return (0);
}

char	**clean_string(char *str, t_data *data)
{
	char	**clean;
	char	*neg;
	char	*ope;

	neg = negative_chars(str, data);
	ope = putspace_between_operateur(neg);
	clean = split_quote(ope, ISSPACE);
	free(neg);
	//free(ope);
	positive_chars(clean);
	return (clean);
}

static int	count_newlen(t_data *data, char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '"')
		{
			while (str[i] && str[i] != '"')
			{
				i++;
				if ((str[i] == '$') && (str[i + 1]) && (is_variable(str[i + 1])))
				{
					i += get_varname_len(&str[i + 1]);
					len += get_varvalue_len(data, &str[i + 1]);
				}
				len++;
			}
			i++;
		}
		else if (str[i] && (str[i] == '$') && (str[i + 1]) && (is_variable(str[i + 1])))
		{
			len += get_varvalue_len(data, &str[i + 1]);
			i += get_varname_len(&str[i + 1]);
		}
		if (!str[i])
			break;
		i++;
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
		i += interpret_ope2(var + i, data, new, j);
		if (ft_isspace(var[i]))
		{
			while (var[i] && ft_isspace(var[i]))
				i++;
			new[*j] = ' ';
			*j += 1;
			i--;
		}
		else
		{
			new[*j] = var[i];
			*j += 1;
		}
	}
	return (get_varname_len(str + 1));
}

void	replace_ope(char **str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		
	}
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

int	interpret_ope(char *str, t_data *data, char *new, int *j)
{
	int	i;
	char quote;

	i = 0;
	quote = '"';
	if (ft_strncmp(str, "\"|\"", 3) == 0 || ft_strncmp(str, "'|'", 3) == 0)
	{
		new[(*j)++] = PIPE;
		return (2);
	}
	else if (ft_strncmp(str, "\">\"", 3) == 0 || ft_strncmp(str, "'>'", 3) == 0)
	{
		new[*j] = CHEVRIGHT;
		(*j)++;
		return (2);
	}
	else if (ft_strncmp(str, "\"<\"", 3) == 0 || ft_strncmp(str, "'<'", 3) == 0)
	{
		new[*j] = CHEVLEFT;
		(*j)++;
		return (3);
	}
	else if (ft_strncmp(str, "\">>\"", 4) == 0 || ft_strncmp(str, "'>>'", 4) == 0)
	{
		new[(*j)++] = CHEVRIGHTD;
		new[(*j)++] = CHEVRIGHTD;
		return (3);
	}
	else if (ft_strncmp(str, "\"<<\"", 4) == 0 || ft_strncmp(str, "'<<'", 4) == 0)
	{
		new[(*j)++] = CHEVLEFTD;
		new[(*j)++] = CHEVLEFTD;
		return (3);
	}
	else if ((ft_strncmp(str, "\"\"", 2) == 0 || ft_strncmp(str, "''", 2) == 0 ) && is_in_charset(str[2], ISSPACE))
		new[(*j)++] = SLASHBACK;
		return (1);
	return (1);
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
			i += interpret_ope(str + i, data, new, &j);
			while (str[i] && str[i] != '"')
			{
				if ((str[i] == '$') && (str[i + 1]) && (is_variable(str[i + 1])))
				{
					i += add_value(new, &str[i],  data, &j);
					if (str[i] == '|')
						new[j++] = ' ';
				}
				else
					new[j++] = (str[i] * -1);
				i++;
			}
			i++;
		}
		else if (str[i] == '\'')
		{
			i += interpret_ope(str + i, data, new, &j);
			while (str[i] && str[i] != '\'')
				new[j++] = (str[i++] * -1);
			i++;
		}
		else if (str[i] == '$' && str[i + 1] && is_variable(str[i + 1]))
			i += add_value_nospace(new, &str[i++],  data, &j);
		else
			new[j++] = str[i++];
	}
	new[j] = 0;
	// _display_pos(new);
	
	return (new);
}

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
