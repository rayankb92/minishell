/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:26:47 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/19 02:29:58 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define CHARSET "<>| "
#define CHEVRON "<>"

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <errno.h>

#define ISSPACE "\t\v\n\r\f "

enum redirect_index
{
	GREAT = 1,// >
	DGREAT,// >>
	LESS,//<
	DLESS,//<<
};

enum operator
{
	PIPE = -1,// >
	CHEVRIGHT = -2,// >
	CHEVLEFT = -3,
	CHEVLEFTD = -4,//<
	CHEVRIGHTD = -5,//<<
	SLASHBACK = -6
};

typedef struct s_sequence
{
	const char	*redirect;
	int			index_redirect;
}	t_sequence;

typedef struct t_file
{
	const char	*redirect;
	int			index_redirect;
}	t_file;

typedef struct s_cmd
{
	char			*command;
	char			**args;

	t_sequence		*sequence;
	int				length_sequence;
	struct s_cmd	*next;
}	t_cmd;

typedef struct	s_env
{
	char			*key;
	char			*value;
	int				equal;

	struct s_env	*next;
}	t_env;

typedef struct t_heredoc
{
	int			pipe[2];
	const char 	*limiter;
	int			expand;
}	t_heredoc;

typedef struct s_data
{
	t_env			*tenv;

	t_cmd			*cmd;
	pid_t			pids[4096];
	int				pipes[2];
	int				prev_pipe;

	char			**path;
	char			**env;

	t_heredoc		*here_doc;
	int				len_here;

	char			**herecopy;
	int				expand;
	struct t_data	*next;
}	t_data;

/*
	DIRECTORY: ./SRC
*/
//	init_data.c
int				init_data(t_data *data, char **env);

/*
	DIRECTORY: ./PARSE
		./
*/
//	parse.c
int				check_quote(const char *str);
int				check_chevrons(const char *str);
char			**split_iscote(char *str);
//	parse_input.c
void			parse_input(const char *input, t_cmd *cmd, t_data *data);
//	utils_parse_input.c
char			*array_to_string(char **array);
void			ft_realloc(char **line, const char *s1);
int				count_occurence(const char *str, const char c);
int				get_length_args(char **ptr);
//	utils.c
int				ft_lstcount(t_cmd *cmd);
int				is_in_charset(char c, char *charset);
int				error_msg(char *str);


void	find_here_doc(char **here, t_data *data);
/*
	DIRECTORY: ./PARSE
		./env
*/
//		tenv.c
t_env			*new_env(char *key, char *value, int eq);
void			add_back_env(t_env **env, t_env *new);

/*
	DIRECTORY: ./PARSE
		./expand
*/
//	expand.c
char			*expand(t_data *data, const char *var);
size_t			get_varvalue_len(t_data *data, const char *var);
size_t			is_variable(const char c);
size_t			get_varname_len(const char *var);
//	clean_string.c
char			**clean_string(char *str, t_data *data);
char			*putspace_between_operateur(char *str);
void			positive_chars(char **str);
//	split_quote.c
char			**split_quote(char const *s, char *charset);
//	add_expand_to_str.c
int				add_varlen_(t_data *data, char *str, int *len);
int				add_value(char *new, char *str, t_data *data, int *j);
int				add_value_nospace(char *new, char *str, t_data *data, int *j);
//	neg_chars.c
char			*negative_chars(char *str, t_data *data);
int				find_char(char c);
/*
	DIRECTORY: ./BUILTINS
*/
//	is_builtin.c
int				is_builtin(t_cmd *cmd, t_data *data);
//	is_exit.c
void			is_exit(char **argument);
//	pwd.c
void			pwd(void);
const char		*pwd_malloc(void);
//	cd.c
void			cd(const char *path);
//	unset.c
int				unset(t_data *data, char *name);
//	echo.c
void			echo(const char **arg, int fd);
//	export.c
void			export(t_data *data, const char *str);

/*
	DIRECTORY: ./EXEC
*/
//	exec.c
void			exec(const char *input, t_data *data);
//	is_heredoc.c
void			is_heredoc(t_data *data, t_cmd *cmd);
int				find_pipe(t_heredoc *tab, const char *limiter, int len);
void			close_pipes(t_heredoc *tab, int read, int write, int len);
//	is_redirection.c
void			is_redirection(t_data *data, t_cmd *ptr);
//	valid_command.c
char			*valid_command(const char *command, char **env);

/*
	DIRECTORY: ./SIGNAL
*/
//	signal.c
void			ctrlc(int sig);

/*
	DIRECTORY: ./
*/
//	print.c
void			print_cmd(t_cmd *cmd);
void			display_lst(t_list *lst);
void			display_env(t_env *env);
/*
	DIRECTORY: ./free
*/
//	free.c
void			free_shell(t_data *data);
void			free_cmd(t_cmd *ptr);
void			free_tenv(t_env *ptr);

t_cmd			*lstlast(t_cmd *cmd);


#endif
