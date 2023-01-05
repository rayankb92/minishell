/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:15:38 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/05 06:04:05 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	handle_quote(char *str, t_data *data)
{
	int	i;
	int	k;
	char **new;
	int start;

	new = malloc(sizeof(char *) * 7);
	i = 0;
	k = 0;
	// ft_printf("Handle cote = ");
	while (str[i])
	{
		while (ft_isspace(str[i]))
		{
			ft_printf("isspace = '%c'\n", str[i]);
			i++;
		}
		if (str[i] != '"')
		{
			ft_printf("la str[%i] = '%c'\n", i, str[i]);
			start = i;
			while (str[i] && !ft_isspace(str[i]))
			{
				ft_printf("IFNOQUOTE str[%i] = '%c'\n", i, str[i]);
				i++;
			}
			new[k++] = ft_substr(str, start, (i - start));
			ft_printf("apres le while str[%i] = %c\n", i, str[i]);
		}
		while (ft_isspace(str[i]))
		{
			ft_printf("isspace = '%c'\n", str[i]);
			i++;
		}
		if (str[i] == '"')
		{
			start = ++i;
			while (str[i] && str[i] != '"')
			{
				ft_printf("ELSE str[%i] = '%c'\n", i, str[i]);
				i++;
			}
			ft_printf("start = %i    | i = %i\n", start, i);
			new[k++] = ft_substr(str, start, (i - start));
			i++;
		}
		while (ft_isspace(str[i]))
		{
			ft_printf("isspace = '%c'\n", str[i]);
			i++;
		}
		if (str[i] == '\'')
		{
			start = ++i;
			while (str[i] && (str[i] != '\'' || !ft_isspace(str[i + 1])))
			{
				ft_printf("SIMPLE str[%i] = '%c'\n", i, str[i]);
				i++;
			}
			ft_printf("start = %i    | i = %i\n", start, i);
			new[k++] = ft_substr(str, start, (i - start));
			i++;
		}
		
			ft_printf("str[%i] = %c\n", i, str[i]);
	}
	new[k] = 0;
	ft_printf("---------\n");
	// ft_printf("new[0] = '%s'\n", new[0]);
	// ft_printf("new[1] = '%s'\n", new[1]);
	// ft_printf("new[2] = '%s'\n", new[2]);
	// ft_printf("new[3] = '%s'\n", new[3]);

	ft_displaydouble(new);
	ft_printf("\n");
}