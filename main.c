/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:47:36 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/23 03:33:11 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void *g_data;

static
void	quit(short status, t_data *data)
{
	free_shell(data);
	rl_clear_history();
	ft_putendl_fd("exit", 2);
	exit(status);
}


void	copy_files(char *find, t_data *data);


int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	const char	*input;
	short		status;
	t_data		data = {0};

	status = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, & ctrlc);
	if (!isatty(STDIN_FILENO))
		return (EXIT_FAILURE);
	while (1)
	{
		input = readline("Fumier$ ");
		if (!input)
			quit(status, & data);
		if (*input)
			add_history(input);
		if (*input && check_chevrons(input) == EXIT_SUCCESS)
		{
			if (check_quote(input) == EXIT_SUCCESS)
			{
				if (init_data(& data, env))
					return (EXIT_FAILURE);
				//copy_files("lala", &data);
				data.expand = 1;
				parse_input(input, data . cmd, & data);
				data.herecopy = split_iscote((char *)input);
				//print_cmd(data.cmd);
				exec(& data);
				g_data = & data;
				//free_shell(& data);
				status = ft_atoi(get_key_from_tenv(data . tenv, "?"));
				free_heredoc(data . here_doc, data . len_here);
				data . here_doc = 0;
				data . len_here = 0;
				free_cmd(data . cmd);
				ft_arraydel(data . path);
				data . path = 0;
				ft_arraydel(data . herecopy);
				data . herecopy = 0;
				data . cmd = 0;
			}
			else
				ft_putstr_fd("Syntax error\n", 2);
		}
		else
			update_status_code(& data, 2);
		ft_memdel((void **)& input);
	}
	quit(status, & data);
}

//chemin absolu affiche pas command not found   ---> Rayan -> pas compris mais sa a l'air de marcher comme bash
//revoirla fonction is_child pour la refacto

//ls | < a > | ls : sytax error
// -------------------------------------------REGLER--------------------"|||||||||||||||||||||||||||||||||||||||||||||||||||||||" - > command notfound like a vrai bash

// _________________________________________________________
// a/b -> not a directory si dossier existe pas				|
// a/b -> not such file or directory si dossier existe		|
// a/b -> permission denied si fichier existe dans dossier	| -------------> FAIT
// _________________________________________________________|

/*
Fumier$ ./signal/
==479867== 
==479867== FILE DESCRIPTORS: 4 open (3 std) at exit.
==479867== Open file descriptor 3: /dev/pts/0
==479867==    at 0x49DD19B: dup (syscall-template.S:120)				--->PAS FAIT Mais ya plus cette erreur
==479867==    by 0x405D7B: exec (exec.c:121)
==479867==    by 0x40720E: main (main.c:66)
*/


/*
==471347==     in use at exit: 208,902 bytes in 246 blocks
==471347==   total heap usage: 1,098 allocs, 852 frees, 248,160 bytes allocated
==471347== 
==471347== 2 bytes in 1 blocks are definitely lost in loss record 3 of 81
==471347==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==471347==    by 0x407A45: ft_strdup (in /mnt/nfs/homes/rferradi/42/42-projets/vogsphere/minishellnorm/minishell)
==471347==    by 0x407F22: ft_substr (in /mnt/nfs/homes/rferradi/42/42-projets/vogsphere/minishellnorm/minishell)
==471347==    by 0x40506F: export (export.c:78)
==471347==    by 0x40360F: update_status_code (t_env_utils.c:47)
==471347==    by 0x4072B2: main (main.c:83)
==471347== 
==471347== 2 bytes in 1 blocks are definitely lost in loss record 4 of 81
==471347==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==471347==    by 0x407A45: ft_strdup (in /mnt/nfs/homes/rferradi/42/42-projets/vogsphere/minishellnorm/minishell)
==471347==    by 0x407F22: ft_substr (in /mnt/nfs/homes/rferradi/42/42-projets/vogsphere/minishellnorm/minishell)
==471347==    by 0x4050B2: export (export.c:81)
==471347==    by 0x40360F: update_status_code (t_env_utils.c:47)
==471347==    by 0x4072B2: main (main.c:83)
==471347== 
==471347== 12 bytes in 1 blocks are still reachable in loss record 11 of 81
==471347==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==471347==    by 0x4024D6: ft_realloc (utils_parse_input.c:80)
==471347==    by 0x406E42: valid_command (valid_command.c:31)
==471347==    by 0x4060B9: is_child (exec.c:46)
==471347==    by 0x405EA1: exec (exec.c:146)
==471347==    by 0x40720D: main (main.c:66)

*/

//export a=">out"
//bash $a =
//bash: >out: No such file or directory

//export a=">out" = impossible
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

//jewancti@e2r7p15:~/Desktop/minishell$ export ab="doihoihf>
//> ^C
//jewancti@e2r7p15:~/Desktop/minishell$ export ab="doihoihf>erge
//> ^C
//jewancti@e2r7p15:~/Desktop/minishell$ export ab=doihoihf>erge
//jewancti@e2r7p15:~/Desktop/minishell$ echo $ab
//doihoihf
//jewancti@e2r7p15:~/Desktop/minishell$ 
