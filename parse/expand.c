/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:15:38 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/07 02:21:31 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Pleins de choses a reprendre
// bcp de fonction"test" a effacer/refaire
// Find var est bon je crois, a verifier
// 

int		get_varname_len(char *var)
{
	int	i;

	i = 0;
	if (!var || !*var)
		return (0);
	while (var[i] && (!ft_isspace(var[i]) && !is_in_charset(var[i], "'\"")))
		i++;
	ft_printf("VARNAME LEN = %i name = %s\n",i,  var); 
	return (i);
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
	{
		ft_printf("findvar------\n");

		return (NULL);
	}
	tmp = data->env;
	len = get_varname_len(var);
	ft_printf("var = %s, len = %i\n", var, len);
	while (tmp)
	{
		// if (ft_strncmp(var, tmp->content, len))
		
		if (ft_strncmp(var, tmp->content, len) == 0 && tmp->content[len] == '=')
			return (ft_substr(tmp->content, len + 1, (ft_strlen(tmp->content))));
		tmp = tmp->next;
	}
	return (NULL);
}




void	expand(char **str, t_data *data)
{
	char	**new;
	char	*ptr;
	int		i;
	int		j, k;
	int		words;

	i = -1;
	while (str[++i])
	{
		
	}
}
