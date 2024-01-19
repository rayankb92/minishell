#include "../include/minishell.h"
#include <libgen.h>
#define MAX_READ_SIZE 50

char *getFolder() {
    char *chemin = NULL;
    long tailleInitiale = pathconf(".", _PC_PATH_MAX);

    if ((chemin = (char *)malloc((size_t)tailleInitiale)) != NULL) {
        char *cheminActuel = getcwd(chemin, (size_t)tailleInitiale);

        if (cheminActuel != NULL) {
            char *nomDossier = basename(cheminActuel);
            char *resultat = strdup(nomDossier);

            if (resultat == NULL) {
                perror("strdup");
                exit(EXIT_FAILURE);
            }

            free(chemin);
            return ft_strjoin(resultat, "/");
        } else {
            perror("getcwd");
        }

        free(chemin);
    } else {
        perror("malloc");
    }

    return ft_strdup("/");
}


typedef struct s_prompt
{
	int					prev;
	int					res;
	int					link[2];
	int					forkstate;
}						t_prompt;

static void	exec_cmd_git(t_prompt *prompt, char **cmd, int choice)
{
	close(prompt->link[0]);
	if (choice == 1)
	{
		dup2(prompt->link[1], STDOUT_FILENO);
		dup2(prompt->link[1], STDERR_FILENO);
		close(prompt->link[1]);
	}
	else if (choice == 2)
	{
		dup2(prompt->prev, STDIN_FILENO);
		dup2(prompt->link[1], STDOUT_FILENO);
		close(prompt->link[1]);
	}
	execve(cmd[0], (char **)cmd, NULL);
	exit(0);
}



static int	get_git_branch(void)
{
	t_prompt			prompt;
	int					res;
	static const char	*command1[3] = {"/usr/bin/git", "branch", 0};
	static const char	*command2[3] = {"/usr/bin/grep", "*", 0};

	pipe(prompt.link);
	prompt.forkstate = fork();
	if (prompt.forkstate == 0)
	{
		exec_cmd_git(&prompt, (char **)command1, 1);
	}
	wait(0);
	prompt.prev = prompt.link[0];
	close(prompt.link[1]);
	pipe(prompt.link);
	prompt.forkstate = fork();
	if (prompt.forkstate == 0)
	{
		exec_cmd_git(&prompt, (char **)command2, 2);
	}
	wait(0);
	close(prompt.link[1]);
	close(prompt.prev);
	res = prompt.link[0];
	return (res);
}


char	*ft_strcpy_maxou(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


char	*build_prompt(short *status)
{
	char		buffer[MAX_READ_SIZE + 1];
	int			fd;
	size_t		red;
	static char	prompt[170];
	char	folder[170];

	sprintf(folder, BB"%s "EB, getFolder());
	
	if (*status == 0)
		ft_strcpy_maxou(prompt, ft_strjoin(GR ARROW EB RB , folder));
	else
		ft_strcpy_maxou(prompt, ft_strjoin(RB ARROW EB RB , folder));
	fd = get_git_branch();
	red = read(fd, buffer, 2);
	buffer[3] = 0;
	if (!red)
		return (close(fd), prompt);
	red = read(fd, buffer, MAX_READ_SIZE);
	close(fd);
	buffer[red - 1] = 0;
	ft_strcat(prompt, BB "git:(" EB);
	ft_strcat(prompt, GR);
	ft_strcat(prompt, buffer);
	ft_strcat(prompt, EB);
	ft_strcat(prompt, BB ") " EB);
	return (prompt);
}
