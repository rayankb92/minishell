/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:42:43 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/07 17:36:36 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		count_occurence(const char *str, const char c)
{
	size_t	i;
	int		occur;

	i = 0;
	occur = 0;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != '\0')
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
		while (input[i] && input[i] != ' ' && input[i] != '<' && input[i] != '>')
			i++;
		sequence[index] . redirect = ft_strndup(input + begin, i - begin);
		while (input[i] && input[i] == ' ')
			i++;
		begin = i;
		while (input[i] && input[i] != '>' && input[i] != '<' && input[i] != '|')
			i++;

		char *suite_args = remove_space(input + begin, i - begin);
		if (suite_args[0] != ' ' && suite_args[1] != '\0' && cmd -> temp_args[0])
			cmd -> temp_args = ft_strjoin(cmd -> temp_args, " ");
		cmd -> temp_args = ft_strjoin(cmd -> temp_args, suite_args);
		index++;
	}
	// set final args as array for execve
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
		while (input_tmp[i] && input_tmp[i] != ' ' && input_tmp[i] != '>' && input_tmp[i] != '<')	
			i++;
		tmp -> command = ft_strndup(input_tmp + last, i - last);
		while (input_tmp[i] && input_tmp[i] == ' ')	
			i++;
		last = i;
		while (input_tmp[i] && input_tmp[i] != '>' && input_tmp[i] != '<')	
			i++;

		tmp -> temp_args = remove_space(input_tmp + last, i - last);
		//tmp -> temp_args = ft_strndup(input_tmp + last, i - last);
		// debut redirection
		occur = count_occurence(input_tmp + i, '>') + count_occurence(input_tmp + i, '<');
		if (occur > 0)
		{
			//tmp -> temp_args = remove_space(input_tmp + last, i - last-1);
			tmp -> sequence = ft_calloc(occur, sizeof(t_sequence));
			tmp -> length_sequence = occur;
			attribute_sequence(i, input_tmp, tmp);
		}
		else
		{
			//tmp -> temp_args = remove_space(input_tmp + last, i - last);
			if (tmp -> temp_args[0])
				tmp -> args = ft_split(tmp -> temp_args, ' ');
			//tmp -> args = ft_split(ft_strjoin(ft_strjoin(tmp -> command, " "), tmp -> temp_args), ' ');
		}
		if (index + 1 == array_len(inputs))
			break ;
		tmp -> next = ft_calloc(sizeof(t_cmd), 1);
		tmp = tmp -> next;
		tmp -> next = 0;
	}
	// adaptation fonction rayan clean_string
	//tmp = cmd;
	//char **res = clean_string((char *)input);
	//int index_res = -1;
	//while (tmp)
	//{
	//	if (tmp -> args)
	//	{
	//		int index_args = 0;
	//		while (tmp -> args[index_args] && res[++index_res])
	//		{
	//			if (ft_strcmp(tmp -> args[index_args], res[index_res]) != 0)
	//				tmp -> args[index_args] = res[index_res];
	//			index_args++;
	//		}		
	//	}
	//	tmp = tmp -> next;
	//}
}
