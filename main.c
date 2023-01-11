/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:47:36 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/11 02:24:46 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static
void	attribute_files(int indexs[4], t_cmd *ptr)
{
	int	i;

	i = -1;
	while (++i < DLESS)
	{
		if (indexs[i] > -1)
		{
			ptr -> files[i] . index_redirect = ptr -> sequence[indexs[i]] . index_redirect;
			ptr -> files[i] . redirect = ptr -> sequence[indexs[i]] . redirect;
		}
		else
			ptr -> files[i] . index_redirect = -1;
	}
}

static
void	set_files(t_cmd *cmd)
{
	t_cmd	*ptr;
	int		indexs[4];
	int		i;

	ptr = cmd;
	indexs[0] = -1;
	indexs[1] = -1;
	indexs[2] = -1;
	indexs[3] = -1;
	while (ptr)
	{
		if (ptr -> sequence)
		{
			i = 0;
			while (i < ptr -> length_sequence)
			{
				if (ptr -> sequence[i] . index_redirect == GREAT)
					indexs[GREAT - 1] = i;
				if (ptr -> sequence[i] . index_redirect == DGREAT)
					indexs[DGREAT - 1] = i;
				if (ptr -> sequence[i] . index_redirect == LESS)
					indexs[LESS - 1] = i;
				if (ptr -> sequence[i] . index_redirect == DLESS)
					indexs[DLESS - 1] = i;
				i++;
			}
			attribute_files(indexs, ptr);
		}
		ptr = ptr -> next;
	}
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	const char	*input;
	t_data		data;
	t_cmd		*cmd;
	t_file		file[2] = {0};
	char		**res;

	if (!env || !*env)
		return (0);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, & ctrlc);
	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (EXIT_FAILURE);
	cmd -> next = 0;
	set_data(env, & data);
	while (1)
	{
		input = readline("Fumier$ ");
		if (!input)
			break ;
		add_history(input);
		if (*input && check_chevrons(input) == EXIT_SUCCESS)
		{
			if (check_quote(input) == EXIT_SUCCESS)
			{
				res = clean_string((char*)input, &data);
				//ft_displaydouble(res);
				parse_input(input, cmd, & data);
				set_files(cmd);
				if (cmd -> command)
				{
					print_cmd(cmd);
					exec(input, cmd, env);
				}
				ft_bzero(cmd, sizeof(t_cmd));
				ft_bzero(cmd -> sequence, sizeof(t_sequence) * cmd -> length_sequence);
			}
			else
				ft_putstr_fd("Syntax error\n", 2);
		}
	}
	return (EXIT_SUCCESS);
}
	
//______________________________________________________________
//| echo "salut" ""'"'"mec" "" [echo] [salut] [] ["] [mec] []	|
//| echo "salut" '"'mec       "" [echo] [salut] ["mec]		|
//| salut "mec													|
//|_____________________________________________________________|

// si un simple quote ouvert on prend tout comme string/commande/arg jusqu'a trouver la la prochaine quote fermante


// ____________________________________
// [echo] [salut] ["'mec] 				|
// 										|
// Fumier >$ echo "salut" '"'m'e'c		|
// must do > [echo] [salut] ["'mec] 
// _____________________________________|

// _________________________________________
// [echo] [salut] ["'m'e'c] 				|
// 											|
// Fumier >$ echo "salut" '"'m'e'c			|
// must do > [echo] [salut] ["mec]
// _________________________________________|	

/*
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd_in, fd_out;
    char *argv[] = {"cat", NULL};
    
    // Ouvrez Makefile en lecture
    fd_in = open("Makefile", O_RDONLY);
    if (fd_in == -1) {
        perror("open");
        return 1;
    }
    // Redirigez l'entrée standard vers Makefile
    if (dup2(fd_in, STDIN_FILENO) == -1) {
        perror("dup2");
        close(fd_in);
        return 1;
    }

    // Ouvrez out en écriture
    fd_out = open("out", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out == -1) {
        perror("open");
        close(fd_in);
        return 1;
    }

    // Redirigez la sortie standard vers out
    if (dup2(fd_out, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(fd_in);
        close(fd_out);
        return 1;
    }
    close(fd_in);
    close(fd_out);

    // Executez la commande "ls"
    execve("/bin/cat", argv, NULL);
    
    perror("execve");
    return 1;
}*/