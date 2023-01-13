/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:35:41 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/13 23:39:24 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_valid_name(char *str)
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

static int	isset_var(t_env *temp, char *name, char *value)
{		
	if (ft_strcmp(temp->key, name) == 0)
	{
		if (value)
		{
			free(temp->value);
			temp->value = value;
			return (0);
		}
	}
	return (1);
}

static void	make_export(t_data *data, char *name, char *value)
{
	t_env	*temp;
	int		len;

	temp = data->tenv;
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

// o--->o--->o--->o--->o--->NUL

// int	export(t_data *data, char *str)
// {
// 	char	*export;
// 	int		len;
// 	t_list	*tmp;

// 	if (!is_valid_name(str))
// 		return (0);
// 	if (ft_strchr(str, '='))
// 		make_export(data, str);
// 	return (0);
// }


int	export(t_data *data, char *str)
{
	char	*export;
	int		len;
	t_list	*tmp;
	char	*varname;
	char	*value;

	len = get_varname_len(str);
	if (!is_valid_name(str))
		return (0);
	varname = ft_substr(str, 0, len);
	value = ft_substr(str, (len + 1), (ft_strlen(str) - len));
	if (!varname)
		return (0);
	make_export(data, varname, value);
	
	
}
