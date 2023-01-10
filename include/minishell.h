/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:26:47 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/10 02:58:42 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define CHARSET "<>| "
#define CHEVRON "<>"

# include "../libft/includes/libft.h"

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>

#define ISSPACE "\t\v\n\r\f "

enum redirect_index
{
	GREAT = 1,// >
	DGREAT,// >>
	LESS,//<
	DLESS,//<<
};

typedef struct s_sequence
{
	const char	*redirect;
	int			index_redirect;
}	t_sequence;

typedef struct s_cmd
{
	char			*command;
	char			*temp_args;
	char			**args;
	
	t_sequence		*sequence;
	int				length_sequence;
	struct s_cmd	*next;
}	t_cmd;

typedef struct t_data
{
	t_list	        *env;
	char			*entry;
	t_cmd			*cmd;
	struct s_lst    *next;
}	t_data;


static	t_data	*return_struct(t_data *data);

/*
	DIRECTORY: PARSE
*/
//	parse.c
int				is_in_charset(char c, char *charset);
void			set_data(char **env, t_data *data);
static size_t	countword(const char *s, char *sep);
void			expand(char **str, t_data *data);
char			**split_quote(char const *s, char *charset);
char			*negative_chars(char *str, t_data *data);
void			positive_chars(char **str);
char			**clean_string(char *str, t_data *data);
int				check_quote(const char *str);
int				check_chevrons(const char *str);
int		get_varname_len(char *var);
//	parse_input.c
void			parse_input(const char *input, t_cmd *cmd, t_data *data);
//	utils_parse_input.c
char			*array_to_string(char **array);
void			ft_realloc(char **line, const char *s1);
int				count_occurence(const char *str, const char c);
int				get_length_args(char **ptr);
//char			*remove_space(const char *s, const int size);
//	expand.c
void			expand(char **str, t_data *data);
int				get_varvalue_len(t_data *data, char *var);
int				is_variable(char c);

//	utils.c
int				error_msg(char *str);
char			*find_var(t_data *data, char *var);
void			display_lst(t_list *lst);
/*
	DIRECTORY: SRC
*/
//	set_data.c
void		set_data(char **env, t_data *data);

/*
	DIRECTORY: BUILTINS
*/
//	is_builtin.c
int			is_builtin(t_cmd *cmd);
//	is_exit.c
void		is_exit(char **argument);
//	pwd.c
void		pwd(void);
const char	*pwd_malloc(void);
//	cd.c
int			cd(const char *path);
//	unset.c
int			unset(t_data *data, char *name);
//	echo.c
void		echo(const char *str, const char opt);
//	export.c
void		export(t_data *data, char *name, char *value);
void		display_list(t_list *lst);

char		*find_var(t_data *data, char *var);
void		exec(const char *input, t_cmd *cmd, char **env);

/*
	DIRECTORY: SIGNAL
*/
//	signal.c
void		ctrlc(int sig);

/*
	DIRECTORY: ./
*/
//	print.c
void		print_cmd(t_cmd *cmd);

#endif
