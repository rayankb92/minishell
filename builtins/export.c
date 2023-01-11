/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:35:41 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/11 00:51:34 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid_name(char *str)
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

int	isset_var(t_list *temp, char *str, int len)
{
	// ft_printf("str = '%s | len = %i\n", str, len);
	if (ft_strncmp(temp->content, str, len) == 0)
	{
		free(temp->content);
		temp->content = str;
		return (0);
	}
	return (1);
}

void	make_export(t_data *data, char *str)
{
	t_list	*temp;
	int		len;

	len = get_varname_len(str);
	temp = data->env;
	while(temp->next)
	{
		if (!isset_var(temp, str, len))
			return ;
		temp = temp->next;
	}
	if (!isset_var(temp, str, len))
			return ;
	temp->next = ft_lstnew(str);
}

// o--->o--->o--->o--->o--->NUL

int	export(t_data *data, char *str)
{
	char	*export;
	int		len;
	t_list	*tmp;

	if (!is_valid_name(str))
		return (0);
	if (ft_strchr(str, '='))
		make_export(data, str);
	return (0);
}
