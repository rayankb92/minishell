/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 06:37:10 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/02 18:15:49 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_in_charset(char c, char *charset)
{
	int	i;

	i = -1;
	while (charset[++i])
		if (c == charset[i])
			return (1);
	return (0);
}

int	error_msg(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}

t_cmd	*cmdnew(char *content)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = ft_split(content, ' ');
	return (cmd);
}
	

void	display_lst(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		ft_printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

// commande en cours
char	**parse_cmd(char *str)
{
	int	i;
	int	j;
	char	**res;

	i = 0;
	j = 0;
	while (str[i + j])
	{

		while (str[i + j] && ft_isspace(str[i + j]) && !is_in_charset(str[i + j], CHARSET))
		{

			i++;
		}
		while (str[i + j] && !ft_isspace(str[i + j]) && !is_in_charset(str[i + j], CHARSET))
		{
			ft_printf("la\n");
			j++;

		}
	}
	res= ft_split(ft_substr(str, 0, (i + j)), ' ');
	return (res);
}
	