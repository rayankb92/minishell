/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:15:38 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/16 17:04:49 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		get_varname_len(char *var)
{
	int	i;

	i = 0;
	if (!var || !*var)
		return (0);
	while (var[i] && (!ft_isspace(var[i]) && !is_in_charset(var[i], "='\"|<>$")))
		i++;
	return (i);
}

int		get_varvalue_len(t_data *data, char *var)
{
	int	i;

	i = 0;
	if (!var || !*var)
		return (0);
	return (ft_strlen(find_var(data, var)));
}

int		is_variable(char c)
{
	if (!ft_isalpha(c) && c != '_')
		return (0);
	return (1);
}


char	*find_var(t_data *data, char *var)
{
	int		i;
	t_env	*tmp;
	int		len;

	if (!is_variable(var[0]))
		return (NULL);
	len = get_varname_len(var);
	tmp = data->tenv;
	while (tmp != NULL)
	{
		if (ft_strncmp(var, tmp->key, len) == 0 && ft_strlen(tmp->key) == len)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
