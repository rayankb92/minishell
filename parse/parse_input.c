/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:42:43 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/15 01:39:39 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static
void	attribute_args(int *start, int *index_args, char **parse, t_cmd *ptr)
{
	int		size_args;
	char	*str;

	size_args = get_length_args(parse);
	if (size_args > 0)
	{
		ptr -> args = ft_calloc(sizeof(char *), size_args + 1); // check malloc
		while (parse[*start])
		{
			str = parse[*start];
			if (((str[0] == '>' || str[0] == '<' || str[0] == '|')
				&& str[1] == '\0')
				|| (ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<<") == 0))
				break ;
			ptr -> args[(*index_args)++] = ft_strdup(parse[(*start)++]);
		}
	}
}

static
int	get_index_redirect(const char *redirect)
{
	int	i;

	i = (redirect[0] == '>') + (redirect[1] == '>');
	if (i != 0)
		return (i);
	i = 2 + (redirect[0] == '<') + (redirect[1] == '<');
	return (i);
}

static
void	attribute_sequence(int *start, int *index_args, char **parse, t_cmd *ptr)
{
	int	index_sequence;

	index_sequence = 0;
	ptr -> sequence = ft_calloc(sizeof(t_sequence), ptr -> length_sequence); // check malloc
	(*start)++;
	while (index_sequence < ptr -> length_sequence)
	{
		ptr -> sequence[index_sequence] . redirect = parse[(*start)];
		ptr -> sequence[index_sequence++] . index_redirect = get_index_redirect(parse[(*start) - 1]);
		if (parse[(*start)])
			(*start)++;
		while (parse[(*start)] &&
			parse[(*start)][0] != '>' &&
			parse[(*start)][0] != '<' &&
			parse[(*start)][0] != '|')
			ptr -> args[(*index_args)++] = parse[(*start)++];
		if (parse[(*start)] && (parse[(*start)][0] == '>' || parse[(*start)][0] == '<'))
			(*start)++;
	}
}

void	parse_input(const char *input, t_cmd *cmd, t_data *data)
{
	t_cmd	*ptr;
	char	**parse;
	char	**split;
	int		k = 0;
	int		index_args = 0;
	int		index_split = 0;

	parse = clean_string((char *)input, data); // check malloc
	char *tmp = array_to_string(parse);
	split = ft_split(tmp, '|'); // check malloc
	if (!split)
		return ;
	ft_memdel((void **)& tmp);
	ptr = cmd;
	while (parse[k])
	{
		index_args = 0;
		ptr -> command = ft_strdup(parse[k]);
		attribute_args(& k, & index_args, parse, ptr);
		if (parse[k])
		{
			ptr -> length_sequence = count_occurence(split[index_split], '>') + count_occurence(split[index_split], '<');
			index_split++;
		}
		if (ptr -> length_sequence > 0)
			attribute_sequence(& k, & index_args, parse, ptr);
		while (parse[k] && parse[k][0] == '|')
			k++;
		if (parse[k])
		{
			ptr -> next = ft_calloc(sizeof(t_cmd), 1); // check malloc
			ptr = ptr -> next;
		}
	}
	//for (int i = 0; parse[i]; i++)
	//	free(parse[i]);
	//free(parse);
	//for (int i = 0; split[i]; i++)
	//	free(split[i]);
	//free(split);
	//ft_arraydel(parse);
	//ft_arraydel(split);
}
