/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:35:41 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/16 00:54:03 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static
int	is_valid_name(const char *str)
{
	int	i;

	i = 0;
	if (*str == '=')
	{
		ft_printf("export: `%s' not a valid identifier\n", str);
		return (0);
	}
	while (str[i] && str[i] != '=')
	{
		if (!is_variable(str[i]))
		{
			ft_printf("export: `%s' not a valid identifier\n", str);
			return (0);
		}
		i++;
	}
	return (1);
}

static
int	isset_var(t_env *temp, char *name, char *value)
{		
	if (ft_strcmp(temp->key, name) == 0)
	{
		if (value)
		{
			ft_memdel((void **)& temp->value);
			temp->value = value;
			return (0);
		}
	}
	return (1);
}

static
void	make_export(t_data *data, char *name, char *value)
{
	t_env	*temp;
	int		len;

	temp = data->env;
	while(temp->next)
	{
		if (!isset_var(temp, name, value))
			return ;
		temp = temp->next;
	}
	if (!isset_var(temp, name, value))
			return ;
	temp->next = new_env(name, value);
}

void	export(t_data *data, const char *str)
{
	char	*export;
	int		len;
	t_list	*tmp;
	char	*varname;
	char	*value;

	len = get_varname_len(str);
	if (!is_valid_name(str))
		return ;
	varname = ft_substr(str, 0, len);
	value = ft_substr(str, (len + 1), (ft_strlen(str) - len));
	if (!varname)
		return ;
	make_export(data, varname, value);
}
