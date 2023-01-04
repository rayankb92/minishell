/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:47:36 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/04 22:30:10 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

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

void	attribute_sequence(const int start, const char *input, t_sequence *sequence, const int size)
{
	int	i;
	int	index;
	int	begin;
	int	index_redirect;

	i = start;
	index = 0;
	while (index < size)
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
		sequence[index] . suite_args = ft_strndup(input + begin, i - begin);
		index++;
	}
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
		while (input_tmp[i] && input_tmp[i] != ' ')	
			i++;
		last = i;
		tmp -> command = ft_strndup(input_tmp, (input_tmp + i) - input_tmp);
		while (input_tmp[i] && input_tmp[i] != '>' && input_tmp[i] != '<' && input_tmp[i] != '|')	
			i++;
		tmp -> args = ft_strndup(input_tmp + last, i - last);
		// debut redirection
		occur = count_occurence(input_tmp + i, '>') + count_occurence(input_tmp + i, '<');
		if (occur > 0)
		{
			tmp -> sequence = calloc(occur, sizeof(t_sequence));
			tmp -> length_sequence = occur;
		}
		attribute_sequence(i, input_tmp, tmp -> sequence, tmp -> length_sequence);
		if (index + 1 == array_len(inputs))
			break ;
		tmp -> next = calloc(sizeof(t_cmd), 1);
		tmp = tmp -> next;
		tmp -> next = 0;
	}
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	const char	*str;
	t_data	data;
	t_cmd	*cmd;

	if (!env || !*env)
		return (0);
	set_data(env, & data);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, & ctrlc);
	cmd = calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (EXIT_FAILURE);
	cmd -> next = 0; // !!
	while (1)
	{
		str = readline("Fumier$ ");
		if (!str)
			break ;
		if (!check_chevrons(str))
		{
			if (check_quote(str) == 1)
			{
				parse_input(str, cmd);
				print_cmd(cmd);
				add_history(str);
				is_exit(str);
			}
		}
		
		; // tres propre gere tout les cas cote non fermer
	}
	return (1);
}
