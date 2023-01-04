/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:47:36 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/04 02:43:59 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int		count_occurence(const char *str, const char c)
{
	int	i;
	int	occur;

	i = 0;
	occur = 0;
	while (str[i])
	{
		if (str[i] == c)
			occur++;
		i++;
	}
	return (occur);
}

void	parse_cmd_jm(const char *input, t_cmd *cmd)
{
	int		i;
	int		last;
	char	*command;

	(void)cmd;
	i = 0;
	while (input[i] && input[i] != ' ')	
		i++;
	last = i;
	command = ft_strndup(input, (input + i) - input);
	ft_printf("command: %s\n", command);
	while (input[i] && input[i] != '>' && input[i] != '<' && input[i] != '|')	
		i++;
	char *args = ft_strndup(input + last + 1, (input + i - 1) - (input + last));
	ft_printf("args: %s\n", args);
	// debut redirection
	int	occur = count_occurence(input + i, '>');
	//cmd -> sequence = malloc(sizeof(t_sequence *) * (occur + 1));
	
	for (int index = 0; index < occur; index++)
	{
		// split to cmd -> args
		int index_redirect = 0;
		while (input[i] && input[i] == '>')
		{
			index_redirect++;
			i++;
		}
		if (index_redirect == 0)
			index_redirect = 2;
		while (input[i] && input[i] == '<')
		{
			index_redirect++;
			i++;
		}
		// set to cmd -> sequence -> index_redirect
		ft_printf("index_redirect: %d\n", index_redirect);
		while (input[i] && input[i] == ' ')
			i++;
		last = i;
		while (input[i] && input[i] != ' ')
			i++;
		// set to cmd -> sequence -> redirect
		char *redirect = ft_strndup(input + last, (input + i) - (input + last));
		ft_printf("redirect: %s\n", redirect);
		while (input[i] && input[i] == ' ')
			i++;
		last = i;
		while (input[i] && input[i] != '>' && input[i] != '<' && input[i] != '|')
			i++;
		char *suite_args = ft_strndup(input + last, (input + i) - (input + last));
		// set to cmd -> sequence -> suite_args
		ft_printf("suite_args: %s\n", suite_args);
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
	while (1)
	{
		str = readline("Fumier$ ");
		if (!str /*|| ft_strcmp(str, "exit") == 0*/)
			break ;
		check_chevrons(str);
		parse_cmd_jm(str, cmd);
		add_history(str);
		is_exit(str);
		//check_quote(str); // tres propre gere tout les cas cote non fermer
	}
	return (1);
}
