/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:25:58 by rferradi          #+#    #+#             */
/*   Updated: 2022/12/30 05:18:21 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#define CHARSET "$<>| "

int	check_quote(char *str)
{
	int	i;

	i = -1;
	int singleopen = 0;
	int	doubleopen = 0;
	while (str[++i])
	{
		if (str[i] == '"' && singleopen == 0 && doubleopen == 0)
			doubleopen = 1;
		else if (str[i] == '"' && singleopen == 0 && doubleopen == 1)
			doubleopen = 0;
		else if (str[i] == 39 && doubleopen == 0 && singleopen == 0)
			singleopen = 1;
		else if (str[i] == 39 && doubleopen == 1 && singleopen == 1)
			singleopen = 0;
		else if (str[i] == 39 && doubleopen == 0 && singleopen == 1)
			singleopen = 0;
	}
	if (singleopen == 1 || doubleopen == 1)
		printf("Syntax Error\n");
	return (1);
}

// 