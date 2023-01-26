/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varvide.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 01:32:19 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/26 16:32:17 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

//ldes  $ok | ls"


static int	many_nb(char *str)
{
	int count = 0;
	int i = 0;
	int chev = 0;
	
	while (str[i] && str[i] != '|')
	{
		while (str[i] && !is_in_charset(str[i], "<>|") && ft_isspace(str[i]))
			i++;
		if (str[i] != VARVIDE && !is_in_charset(str[i], "<>|"))
			count++;
		while (str[i] && !ft_isspace(str[i]) && str[i] != '|')
			i++;
	}
	return (count);
}

static char	*epurstr(char *str)
{
	int len = ft_strlen(str);
	char *s, *new;

	s = str;
	new = malloc(sizeof(char) * ft_strlen(str) + 1);
	int j = 0;
	while (len && ft_isspace(s[len - 1]))
		--len;
	while (len && ft_isspace(*s) && *s++)
		--len;
	while (len--)
	{
		if (!ft_isspace(*s) || (*(s + 1) && !ft_isspace(*(s + 1))))
			new[j++] = *s;
		s++;
	}
	new[j] = 0;
	return (new);
}

static char *retransform(char *str)
{
	char *new;
	char *epur;
	int i;
	int j;

	new = malloc(sizeof(char) * ft_strlen(str) + 1);
	epur = epurstr(str);
	i = 0;
	j = 0;
	free(str);
	while (epur[i])
	{
		if (epur[i] && is_in_charset(epur[i], "<>") && epur[i + 1] && epur[i + 2] && is_in_charset(epur[i + 2], "<>"))
		{
			new[j++] = epur[i++];
			new[j++] = ' ';
			new[j++] = SLASHBACK;
			new[j++] = ' ';
		}
		else if (epur[i] && is_in_charset(epur[i], "<>") && !epur[i + 1])
		{
			new[j++] = epur[i++];
			new[j++] = ' ';
			new[j++] = SLASHBACK;

		}
		else
			new[j++] = epur[i++];
	}
	new[j] = 0;
	free(epur);
	return (new);
}

char *transform_string(char *str)
{
	char	*new;
	int		j;
	int		i;
	int nbword;


	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	nbword = many_nb(str);
	while (str[i])
	{
			if (str[i] && is_in_charset(str[i], "|"))
				nbword = many_nb(&str[i] + 1);
			if (str[i] == VARVIDE && nbword == 0)
			{
				new[j++] = VARVIDE;
				i++;
			}
			else if (str[i] == VARVIDE)
				i++;
			else if (str[i])
				new[j++] = str[i++];
		// i++;
	}
	new[j] = 0;
	//ft_printf("NEW ='%s'\n", new);
	return (retransform(new));
}
