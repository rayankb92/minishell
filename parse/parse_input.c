/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:42:43 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/08 08:17:25 by jewancti         ###   ########.fr       */
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

//int		count_occurence2(const char **str, const char c)
//{
//	size_t	i;
//	int		occur;

//	i = 0;
//	occur = 0;
//	while (str[i])
//	{
//		if (str[i][0] == c && str[i + 1] != 0)
//		{
//			if (str[i + 1][0] == c)
//				i++;
//			occur++;
//		}
//		i++;
//	}
//	return (occur);
//}

//void	attribute_sequence(const int start, const char *input, t_cmd *cmd)
//{
//	int	i;
//	int	index;
//	int	begin;
//	int	index_redirect;
//	t_sequence	*sequence;

//	sequence = cmd -> sequence;
//	i = start;
//	index = 0;
//	while (index < cmd -> length_sequence)
//	{
//		index_redirect = 0;
//		while (input[i] && input[i] == '>')
//		{
//			index_redirect ++;
//			i++;
//		}
//		if (index_redirect == 0)
//			index_redirect = 2;
//		while (input[i] && input[i] == '<')
//		{
//			index_redirect++;
//			i++;
//		}
//		sequence[index] . index_redirect = index_redirect;
//		while (input[i] && input[i] == ' ')
//			i++;
//		begin = i;
//		while (input[i] && input[i] != ' ' && input[i] != '<' && input[i] != '>')
//			i++;
//		sequence[index] . redirect = ft_strndup(input + begin, i - begin);
//		while (input[i] && input[i] == ' ')
//			i++;
//		begin = i;
//		while (input[i] && input[i] != '>' && input[i] != '<' && input[i] != '|')
//			i++;

//		char *suite_args = remove_space(input + begin, i - begin);
//		if (suite_args[0] != ' ' && suite_args[1] != '\0' && cmd -> temp_args[0])
//			cmd -> temp_args = ft_strjoin(cmd -> temp_args, " ");
//		cmd -> temp_args = ft_strjoin(cmd -> temp_args, suite_args);
//		index++;
//	}
//	// set final args as array for execve
//	cmd -> args = ft_split(cmd -> temp_args, ' ');
//}

int		array_len(char **ptr)
{
	int	i;

	i = -1;
	while (ptr[++i])
		;
	return (i);
}

int		get_real_size(char **ptr)
{
	int	i;
	int	size;

	size = 1;
	i = 1;
	while (ptr[i])
	{
		while (ptr[i] && ptr[i][0] != '>' && ptr[i][0] != '<')
		{
			size++;
			i++;
		}
		if (ptr[i] && (ptr[i][0] == '>' || ptr[i][0] == '<'))
			i += 2;
	}
	ft_printf("Getrealsize: %d\n", size);
	return (size);
}

void	ft_realloc(char **line, const char *s1)
{
	char	*res;
	int		i;

	if (*line && **line)
	{
		i = 0;
		while ((*line)[i])
			i++;
		res = malloc(ft_strlen(*line) + i + 2);
		if (res)
		{
			ft_strcpy(res, *line);
			ft_strcpy(res + i, s1);
			free(*line);
			*line = res;
		}
		return ;
	}
	if (*line && !**line)
		free(*line);
	*line = ft_strdup(s1);
}

int		get_length_args(const char **args)
{
	int	i;

	i = 0;
	while (args[i]
			&& args[i][0] != '>' && args[i][0] != '<' && args[i][0] != ' ')
		i++;
	return (i);
}

char	*array_to_string(char **array)
{
	char	*tostring;
	int		i;

	i = 0;
	tostring = 0;
	while (array[i])
	{
		if (array[i + 1] == 0)
			ft_realloc(& tostring, array[i]);
		else
			ft_realloc(& tostring, ft_strjoin(array[i], " "));
		i++;
	}
	return (tostring);
}

void	parse_input(const char *input, t_cmd *cmd)
{
	char	**parse;
	char	**split;
	int		size_split;
	int		size_args;
	char	*tostring;
	int		index_args;
	t_cmd	*ptr;

	parse = clean_string((char *)input);
	ft_displaydouble(parse);
	tostring = array_to_string(parse);
	split = ft_split(tostring, '|');
	size_split = array_len(split);
	ft_printf("tostring: [%s]\n", tostring);
	ptr = cmd;
	int k = 0;
	index_args = 0;
	int index_sequence;
	//for (int i = 0; i < size_split; i++)
	while (parse[k])
	{
		index_sequence = 0;
		index_args = 0;
		ptr -> command = parse[k];
		size_args = get_real_size(parse);
		if (size_args > 0)
		{
			ptr -> args = ft_calloc(sizeof(char *), size_args + 1);
			while (parse[k] && parse[k][0] != '>' && parse[k][0] != '<' && parse[k][0] != '|')
				ptr -> args[index_args++] = parse[k++];
		}
		if (!parse[k])
			break ;
		ptr -> length_sequence = count_occurence(tostring, '>') + count_occurence(tostring, '<');
		if (ptr -> length_sequence > 0)
		{
			k++;
			ptr -> sequence = ft_calloc(sizeof(t_sequence), ptr -> length_sequence);
			while (index_sequence < ptr -> length_sequence)
			{
				ft_printf(">>[%d] %d | %d\n", k, index_sequence, ptr -> length_sequence);
				ptr -> sequence[index_sequence++] . redirect = parse[k];
				ft_printf("redirect: %s\n", parse[k]);
				k++;
				while (parse[k] && parse[k][0] != '>' && parse[k][0] != '<' && parse[k][0] != '|')
					ptr -> args[index_args++] = parse[k++];
				if (parse[k] && (parse[k][0] == '>' || parse[k][0] == '<' || parse[k][0] == '|'))
					k++;
			}
		}
		ft_printf("AFTER: %s\n", parse[k]);
		while (parse[k] && parse[k][0] == '|')
			k++;
		ptr -> next = ft_calloc(sizeof(t_cmd), 1);
		ptr = ptr -> next;	
	}
}
