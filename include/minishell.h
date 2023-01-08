/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:26:47 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/08 19:46:01 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define CHARSET "<>| "
#define CHEVRON "<>"

# include "../libft/includes/libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

enum redirect_index
{
	GREAT = 1,
	DGREAT,
	LESS,
	DLESS,
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

/*
	DIRECTORY: PARSE
*/
//	parse.c
int				is_in_charset(char c, char *charset);
void			set_data(char **env, t_data *data);
static size_t	countword(const char *s, char *sep);
void			expand(char **str, t_data *data);
char			**split_quote(char const *s, char *charset);
char			*negative_chars(char *str);
void			positive_chars(char **str);
static int		count_newlen(char *str);
char			**clean_string(char *str);
int				check_quote(const char *str);
int				check_chevrons(const char *str);
//	parse_input.c
void			parse_input(const char *input, t_cmd *cmd);
//	utils_parse_input.c
char			*array_to_string(char **array);
void			ft_realloc(char **line, const char *s1);
int				count_occurence(const char *str, const char c);
int				get_length_args(char **ptr);
//char			*remove_space(const char *s, const int size);
//	expand.c
void			expand(char **str, t_data *data);
void			handle_quote(char *str, t_data *data);
//	utils.c
int				error_msg(char *str);

/*
	DIRECTORY: SRC
*/
//	set_data.c
void		set_data(char **env, t_data *data);

/*
	DIRECTORY: BUILTINS
*/
//	builtins.c
const char	*pwd(void);
int			cd(const char *path);
int			unset(t_data *data, char *name);
void		echo(char * str, char opt);
void		export(t_data *data, char *name, char *value);
void		display_list(t_list *lst);
void		exit_(t_data *data);

char	*find_var(t_data *data, char *var);
void	exec(t_cmd *cmd);
/*
	DIRECTORY: SIGNAL
*/
//	signal.c
void		ctrlc(int sig);

/*
	DIRECTORY: INTERPRET_INPUT
*/
//	interpret_input.c -> inutile je pense
void		interpret_input(const char *input);
int			is_specifier(const char *specifier, char **match);
//	is_exit.c
void		is_exit(const char *entry);

/*
	DIRECTORY: ./
*/
//	print.c
void		print_cmd(t_cmd *cmd);


int		parse_cmd(t_data *data);
t_cmd	*cmdnew(char *content);
#endif
