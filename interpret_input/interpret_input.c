/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:05:34 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/03 23:54:57 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

# define SIZEMATCH	1

static int	matching(const char const *matchs[SIZEMATCH], const char *match)
{
	const char const	*tmp;
	int					i;

	i = 0;
	while (i < SIZEMATCH)
	{
		if (ft_strcmp(matchs[i], match) == 0)
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

const char	*is_specifier(const char *specifier)
{
	static const char const *matchs[SIZEMATCH] = {"exit"};
	const char				*copy;
	const char				*begin;
	const char				*match;
	int						ret;

	begin = specifier;
	copy = specifier;
	while (ft_isspace(*copy))
		copy++;
	begin = copy;
	while (*copy && !ft_isspace(*copy))
		copy++;
	if (begin == copy)
		return (0);
	match = ft_strsub(specifier, begin - specifier, copy - specifier);
	ret = matching(matchs, match);
	ft_memdel((void **)& match);
	return (begin);
}

void		interpret_input(const char *input)
{
	const char	*specifier;
	char		*first_trim;
	char		*last_trim;

	if (!input || !*input)
		return ;
	specifier = is_specifier(input);
	if (!specifier)
		return ;
	is_exit(specifier);
}
