/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_displaydouble.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:49:46 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/15 16:48:03 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_displaydouble(char **str)
{
	int	i;

	i = -1;
	if (!str || !*str)
		return ;
	while (str[++i])
		ft_printf("[%s] ", str[i]);
	ft_putchar('\n');
}