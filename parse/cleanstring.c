/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanstring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 01:26:17 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/07 02:34:00 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


char	**clean_string(char *str, t_data *data)
{
	char	**clean;
	char	*neg;

	neg = negative_chars(str, data);
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

int	add_value(char *new, char *str, t_data *data, int *j)
{
	int		i;
	char	*var;

	i = -1;
	var = find_var(data, str + 1);
	ft_printf("str = '%c'\n", str[0]);
	ft_printf("laaaa valeur de %s = '%s'\n\n", str, var);
	if (!var)
		return (get_varname_len(str + 1));
	while (var[++i])
	{
		new[*j] = var[i] * -1;
		*j += 1;
	}
	return (get_varname_len(str + 1));
}


char	*negative_chars(char *str, t_data *data)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char ) * (ft_strlen(str) + 200));
	while (str[i])
	{
		if (str[i] == '"')
		{
			while (str[++i] && str[i] != '"')
			{
				ft_printf("str[%i] = '%c'\n", i, str[i]);
				if ((str[i] == '$') && (str[i + 1]) && (is_variable(str[i + 1])))
				{
					i += add_value(new, &str[i],  data, &j);
					ft_printf("value of i = %i | str[%i] = '%c' value of j = %i\n", i, i, str[i], j);
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
			i += add_value(new, &str[i],  data, &j);
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
