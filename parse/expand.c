/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:15:38 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/06 03:55:57 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Pleins de choses a reprendre
// bcp de fonction"test" a effacer/refaire
// Find var est bon je crois, a verifier
// 


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
	len = ft_strlen(var);
	ft_printf("var = %s, len = %i\n", var, len);
	while (tmp)
	{
		if (ft_strncmp(var, tmp->content, (len == 0 && tmp->content[len] == '=')))
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

	i = 0;
	k = 0;
	j = 0;
	// words = countword(str, CHARSET);
	// ft_print	f("%s\n", data->cmd->args[0]);

	data->cmd->args = ft_calloc(sizeof(char *), 6);
	ft_printf("la\n");
	// new = malloc(sizeof(char) * ft_strlen(data->entry));
	while (str[i])
	{
		if (str[i][0] == '$' && is_variable(str[i][1]))
		{
			printf("str == %s\n", str[i]);
			data->cmd->args[k] = find_var(data, str[i] + 1);
			if (data->cmd->args[k])
				k++;
		}
		else
		{
			data->cmd->args[k++] = str[i];
		}
		i++;
	}
	data->cmd->args[k] = 0;
}
