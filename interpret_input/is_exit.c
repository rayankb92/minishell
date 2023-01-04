/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:14:28 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/04 22:49:47 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_set(const char *set, char c)
{
	while (*set && *set != c)
		set++;
	return (*set != '\0');
}

char	*ft_strtrim_middle(const char *s1, const char *tofind, const char *set)
{
	const char	*start;
	const char	*s;
	size_t		len;
	size_t		i;
	size_t		j;

	if (!s1 || !set || !tofind)
		return (0);
	i = 0;
	len = ft_strlen(tofind);
	while (s1[i])
	{
		j = 0;
		while (tofind[j] && s1[i + j] && s1[i + j] == tofind[j])
			j++;
		if (j == len)
			break ;
		i++;
	}
	s = s1 + (i + j);
	start = s;
	while (*s && is_set(set, *s))
		s++;
	if (!*s || s == start)
		return ((char *)start);
	return ((char *)s);
}
// not done : multiple argument && is numeric ?
// AND max value accepted = long long int : 9223372036854775807
void	is_exit(const char *entry)
{
	char		*first_trim;
	char		*last_trim;

	if (!*entry)
		return ;
	first_trim = ft_strtrim(entry, " ");
	last_trim = ft_strtrim_middle(first_trim, "exit", " ");
	if (ft_strncmp(first_trim, "exit", 4) == 0)
	{
		if (ft_atoi(last_trim) == 0)
			ft_printf("bash: exit: %s: numeric argument required\n", last_trim);
		else
			ft_putendl("exit");
		int temp = ft_atoi(last_trim);
		ft_memdel((void **)& first_trim);
		exit(temp);
	}
	ft_memdel((void **)& first_trim);
}
