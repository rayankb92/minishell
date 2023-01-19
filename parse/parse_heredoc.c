/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:27:26 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/19 03:16:58 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#define ISSEP "\t\v\n\r\f <>|"

int	countlen(char *str)
{
	int i = 0;
	int	word = 0;
	char quote;

	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i])
			word++;
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			i++;
		}
		else if (str[i] && is_in_charset(str[i], "|><"))
		{
			i++;
			if (str[i - 1] == str[i])
				i++;
		}
		else
			while (!is_in_charset(str[i], ISSEP))
			i++;
	}
	return (word);
}

int	lenword(char *str)
{
	int	i;
	int	j;
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
		while (is_in_charset(str[i + j], "<>|"))
			j++;
	return (j);
}

char	*fill_tab(char **ptr)
{
	int i;
	char *word;
	char	quote;
	int		lenw;
	char *str;

	str = *ptr;
	lenw = lenword(str);
	i = 0;
	word = malloc(sizeof(char) * (lenw + 1));
	// ft_printf("len str = %i | str = %s\n", lenw, str);
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '"' || *str == '\'')
	{
		quote = *str;
		word[i++] = *str++;
		while (*str && *str != quote)
			word[i++] = *str++;
		word[i++] = *str++;
	}
	else if (*str && is_in_charset(*str, "|><"))
	{
		word[i++] = *str++;
		if (word[i - 1] == *str)
			word[i++] = *str++;
	}
	else
		while (!is_in_charset(*str, ISSEP))
		{
			word[i++] = *str;
			str++;
		}
	word[i] = 0;
	*ptr = str;
	return (word);
}

char **split_iscote(char *str)
{
	int		len;
	char	**new;
	int		i;

	i = -1;
	len = countlen(str);
	new = malloc(sizeof(char *) * (len + 1));
	while (++i < len)
		new[i] = fill_tab(&str);
	new[i] = 0;
	return (new);
}

char	*re_clean(char *str, t_data *data)
{
	char	*result;
	char		**strr;

	strr = clean_string(str, data);
	result = ft_strdup(*strr);
	// ft_arraydel(strr);
	// 	ft_printf("str = %s\n", *str);
	return (result);
}

void	find_here_doc(char **here, t_data *data)
{
	int i = -1;
	int count = 0;
	char *test;

	while (here[++i])
	{
		if (ft_strcmp(here[i], "<<") == 0)
		{
			i++;
			if (ft_strchr(here[i], '"') || ft_strchr(here[i], '\''))
				data->here_doc[count].expand = 1;
			else
				data->here_doc[count].expand = 0;
			data->here_doc[count].limiter = re_clean(here[i], data);

			// test = re_clean(here[i], data);
			count++;
		}
	}
}


// // "salut'bg'ok"

// char	**re_change_delim(char **str, t_data *data)
// {
// 	int	i;
// 	int	j;
// 	char **res;

// 	i = -1;
// 	j = 0;
// 	while (str[++i])
// 	{
// 		if (strcmp(str[i], "<<") == 0)
// 		{
// 			i++;
// 			res = re_clean(str[i], data);
// 		}
// 	}
// 	return (res);
// }
