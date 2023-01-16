/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitquote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:47:26 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/16 17:21:58 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**cleaner(char ***str, int len)
{
	while (--len >= 0)
		ft_memdel((void **)& (*str)[len]);
	ft_memdel((void **)& *str);
	return (0);
}

int	countword_r(const char *s, char *charset)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	int	singleopen, doubleopen;
	singleopen = 0;
	doubleopen = 0;
	while (s[i])
	{
		while (s[i] && is_in_charset(s[i], charset))
			i++;
		if (!is_in_charset(s[i], charset) && s[i])
			count++;
		while (s[i] && !is_in_charset(s[i], charset))
			i++;
	}
	return (count);
}

char	*put_in_tab(const char *s, int *i, char *charset)
{
	static int	j;
	int			index;
	char		*res;

	j = 0;
	index = 0;
	while (is_in_charset(s[*i], charset) && s[*i])
		(*i)++;
	while (!is_in_charset(s[*i + j], charset) && s[*i + j])
		j++;
	res = malloc(sizeof(char) * j + 1);
	if (!res)
		return (NULL);
	while (index < j)
	{
		res[index] = s[*i];
		index++;
		(*i)++;
	}
	res[index] = 0;
	return (res);
}

char	**split_quote(char const *s, char *charset)
{
	char **res;
	int i;
	int j;
	int lenword;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	lenword = countword_r(s, charset);
	res = malloc(sizeof(char *) * (lenword + 1)); // manque plus 1 va savoir pk
	if (!res)
		return (NULL);
	while (i < lenword)
	{
		res[i] = put_in_tab(s, &j, charset);
		if (res[i] == NULL)
			return (cleaner(&res, i));
		i++;
	}
	res[i] = NULL;
	return (res);
}

//**args [echo] [oppsalut''               rejrenkm] [e] [   'c''fghfg]
// cmd = args[0];
//execve(cmd, args);