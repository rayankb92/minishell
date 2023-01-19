/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:15:38 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/19 13:12:51 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

char	*expand(t_data *data, const char *var)
{
	t_env	*tmp;
	size_t	len;

	if (!var)
		return (0);
	if (!is_variable(var[0]))
		return (NULL);
	len = get_varname_len(var);
	tmp = data->tenv;
	fprintf(stderr, "%p | %p | %p\n", tmp, tmp -> key, tmp -> value);
	while (tmp && tmp -> key)
	{
		if (ft_strncmp(var, tmp->key, len) == 0 && ft_strlen(tmp->key) == len)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

size_t	get_varname_len(const char *var)
{
	int	i;

	i = 0;
	if (!var || !*var)
		return (0);
	while (var[i] && (!ft_isspace(var[i]) && !is_in_charset(var[i], "='\"|<>$")))
		i++;
	return (i);
}

size_t	get_varvalue_len(t_data *data, const char *var)
{
	if (!var || !*var)
		return (0);
	return (ft_strlen(expand(data, var)));
}

size_t	is_variable(const char c)
{
	if (!ft_isalpha(c) && c != '_')
		return (0);
	return (1);
}
