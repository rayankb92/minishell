/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:15:38 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/08 22:49:13 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		get_varname_len(char *var)
{
	int	i;

	i = 0;
	if (!var || !*var)
		return (0);
	while (var[i] && (!ft_isspace(var[i]) && !is_in_charset(var[i], "'\"|<>")))
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
	if (ft_isalpha(c) || c == '_')
		return (1);
	return (0);
}

char	*find_var(t_data *data, char *var)
{
	int		i;
	t_list	*tmp;
	int		len;

	if (!is_variable(var[0]))
		return (NULL);
	tmp = data->env;
	len = get_varname_len(var);
	while (tmp)
	{
		if (ft_strncmp(var, tmp->content, len) == 0 && tmp->content[len] == '=')
			return (ft_substr(tmp->content, len + 1, (ft_strlen(tmp->content))));
		tmp = tmp->next;
	}
	return (NULL);
}


// void	expand(char **str, t_data *data)
// {
// 	char	**new;
// 	char	*ptr;
// 	int		i;
// 	int		j, k;
// 	int		words;

// 	i = -1;
// 	while (str[++i])
// 	{
		
// 	}
// }
