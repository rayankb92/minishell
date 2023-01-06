/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:42:43 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/06 16:25:29 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		count_occurence(const char *str, const char c)
{
	size_t	i;
	size_t	size;
	int		occur;

	i = 0;
	occur = 0;
	size = ft_strlen(str);
	while (str[i])
	{
		if (i < size - 2 && str[i] == c)
		{
			if (str[i + 1] == c)
				i++;
			occur++;
		}
		i++;
	}
	return (occur);
}

void	attribute_sequence(const int start, const char *input, t_cmd *cmd)
{
	int	i;
	int	index;
	int	begin;
	int	index_redirect;
	t_sequence	*sequence;

	sequence = cmd -> sequence;
	i = start;
	index = 0;
	while (index < cmd -> length_sequence)
	{
		index_redirect = 0;
		while (input[i] && input[i] == '>')
		{
			index_redirect ++;
			i++;
		}
		if (index_redirect == 0)
			index_redirect = 2;
		while (input[i] && input[i] == '<')
		{
			index_redirect++;
			i++;
		}
		sequence[index] . index_redirect = index_redirect;
		while (input[i] && input[i] == ' ')
			i++;
		begin = i;
		while (input[i] && input[i] != ' ')
			i++;
		sequence[index] . redirect = ft_strndup(input + begin, i - begin);
		while (input[i] && input[i] == ' ')
			i++;
		begin = i;
		while (input[i] && input[i] != '>' && input[i] != '<' && input[i] != '|')
			i++;

		char *suite_args = remove_space(input + begin, i - begin);
		// set final args as array for execve
		cmd -> temp_args = ft_strjoin(cmd -> temp_args, suite_args);
		index++;
	}
	cmd -> args = ft_split(cmd -> temp_args, ' ');
}

int		array_len(char **ptr)
{
	int	i;

	i = -1;
	while (ptr[++i])
		;
	return (i);
}

void	parse_input(const char *input, t_cmd *cmd)
{
	int		i;
	int		index;
	int		last;
	int		occur;
	char	**inputs;
	char	*input_tmp;
	char	*command;
	t_cmd	*tmp;

	if (!*input)
		return ;
	inputs = ft_split(input, '|');
	if (!inputs)
		return ;
	index = -1;
	tmp = cmd;
	while (inputs[++index])
	{
		i = 0;
		input_tmp = inputs[index];
		while (input_tmp[i] && input_tmp[i] == ' ')	
			i++;
		last = i;
		while (input_tmp[i] && input_tmp[i] != ' ')	
			i++;
		tmp -> command = ft_strndup(input_tmp + last, i - last);
		while (input_tmp[i] && input_tmp[i] == ' ')	
			i++;
		last = i; // belek le + 1 == temp args to delete
		while (input_tmp[i] && input_tmp[i] != '>' && input_tmp[i] != '<' && input_tmp[i] != '|')	
			i++;
			
		tmp -> temp_args = remove_space(input_tmp + last, i - last);
		//tmp -> temp_args = ft_strndup(input_tmp + last, i - last);
		// debut redirection
		occur = count_occurence(input_tmp + i, '>') + count_occurence(input_tmp + i, '<');
		if (occur > 0)
		{
			tmp -> sequence = calloc(occur, sizeof(t_sequence));
			tmp -> length_sequence = occur;
			attribute_sequence(i, input_tmp, tmp);
		}
		else
			tmp -> args = ft_split(tmp -> temp_args, ' ');
		if (index + 1 == array_len(inputs))
			break ;
		tmp -> next = calloc(sizeof(t_cmd), 1);
		tmp = tmp -> next;
		tmp -> next = 0;
	}
}
