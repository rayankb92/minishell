/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 20:30:25 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/04 00:35:54 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	char	*s;

	s = malloc(n + 1);
	if (s)
	{
		i = -1;
		while (++i < n && *s1)
			*s++ = *s1++;
		*s = 0;
		s -= i;
	}
	return (s);
}
