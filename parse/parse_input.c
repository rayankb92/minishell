/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:42:43 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/18 20:40:50 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static
char	*positive_stringchar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == PIPE)
			str[i] = '|';
		if (str[i] == CHEVRIGHT)
			str[i] = '>';
		if (str[i] == CHEVLEFT)
			str[i] = '<';
		if (str[i] == SLASHBACK)
			str[i] = '\0';
	}
	return (str);
}

static
char	**positive_arraychars(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		positive_stringchar(str[i]);
	return (str);
}

static
void	to_positive(t_cmd *cmd)
{
	t_cmd	*ptr;

	ptr = cmd;
	while (ptr)
	{
		if (ptr -> command)
			positive_stringchar(ptr -> command);
		if (ptr -> args)
			positive_arraychars(ptr -> args);
		//for (int i = 0; i < ptr -> length_sequence; i++) {
		//	positive_stringchar(ptr -> sequence[i] . redirect);
		//}
		ptr = ptr -> next;
	}
}

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
	if (!parse[*start + 1])
		return ;
	ptr -> sequence = ft_calloc(sizeof(t_sequence), ptr -> length_sequence); // check malloc
	(*start)++;
	while (index_sequence < ptr -> length_sequence)
	{
		if (!parse[*start])
			return ;
		ptr -> sequence[index_sequence] . redirect = ft_strdup(parse[(*start)]);
		ptr -> sequence[index_sequence++] . index_redirect = get_index_redirect(parse[(*start) - 1]);
		if (parse[(*start)])
			(*start)++;
		while (parse[(*start)] &&
			parse[(*start)][0] != '>' &&
			parse[(*start)][0] != '<' &&
			parse[(*start)][0] != '|')
			ptr -> args[(*index_args)++] = ft_strdup(parse[(*start)++]);
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
	//ft_displaydouble(parse);
	if (!parse || !parse[0])
	{
		if (!parse[0])
			free(parse);
		return ;
	}
	char *tmp = array_to_string(parse);
	split = ft_split(tmp, '|'); // check malloc
	ft_memdel((void **)& tmp);
	if (!split)
		return ;
	ptr = cmd;
	int e;
	while (parse[k])
	{
		e = 0;
		index_args = 0;
		while (parse[k][e] == '>' || parse[k][e] == '<')
			e++;
		if (parse[k][e] != '\0')
			ptr -> command = ft_strdup(parse[k]);
		attribute_args(& k, & index_args, parse, ptr);
		if (parse[k])
		{
			ptr -> length_sequence = count_occurence(split[index_split], '>') + count_occurence(split[index_split], '<');
			index_split++;
		}
		else
			ptr -> length_sequence = 0;
		if (ptr -> length_sequence > 0)
			attribute_sequence(& k, & index_args, parse, ptr);
		while (parse[k] && parse[k][0] == '|')
			k++;
		if (!ptr -> command && ptr -> args && ptr -> args[0])
			ptr -> command = ft_strdup(ptr -> args[0]);
		if (parse[k])
		{
			ptr -> next = ft_calloc(sizeof(t_cmd), 1); // check malloc
			ptr = ptr -> next;
		}
	}
	to_positive(cmd);
	ft_arraydel(parse);
	ft_arraydel(split);
}
