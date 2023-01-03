/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:54:17 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/03 16:56:49 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t	countword(const char *s, char *sep)
{
	int		i;
	size_t	len;

	len = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && is_in_charset(s[i], sep) == 1)
			i++;
		if (s[i])
			len++;
		while (s[i] && is_in_charset(s[i], sep) == 0)
			i++;
	}
	ft_printf("len  %d\n", len);
	return (len);
}

void	wordfill(char **tab, const char *s, char *sep, size_t len)
{
	int		i;
	int		j;
	int		k;
	size_t	index;

	i = 0;
	index = 0;
	while (index < len)
	{
		while (s[i] && is_in_charset(s[i], sep) == 1)
			i++;
		j = i;
		while (s[j] && is_in_charset(s[j], sep) == 0)
			j++;
		tab[index] = malloc((j - i) + 1);
		if (!tab[index])
			return ;
		k = 0;
		while (i < j)
			tab[index][k++] = s[i++];
		tab[index][k] = 0;
		index++;
	}
	tab[index] = 0;
}

char	**split_cmd(char const *s, char *sep)
{
	char	**res;
	size_t	len;

	if (!s)
		return (NULL);
	len = countword(s, sep);
	res = malloc(sizeof(char *) * (len + 1));
	if (res)
		wordfill(res, s, sep, len);
	return (res);
}
