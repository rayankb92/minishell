/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:26:47 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/06 03:23:16 by rferradi         ###   ########.fr       */
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

typedef struct t_cmd{
	char			*cmd;
	char			**args; //{ls, -la};; // ls -la || ls > a -la
	int				redir; // a mettre dans une structure avec file
	char			*file;	
	struct t_cmd	*next;
}				t_cmd;

typedef struct t_data{
	t_list	        *env;
	char			*entry;
	t_cmd			*cmd;
	struct s_lst    *next;
}               t_data;

//	parse.c
int				check_quote(const char *str);
int				check_operateur(char *str);
int				is_in_charset(char c, char *charset);
int				error_msg(char *str);
int				check_chevrons(const char *str);
void			set_data(char **env, t_data *data);
static size_t	countword(const char *s, char *sep);
void			expand(char **str, t_data *data);
char			**split_quote(char const *s, char *charset);
char			*negative_chars(char *str);
void			positive_chars(char **str);
static int		count_newlen(char *str);
char			**clean_string(char *str);

//	builtins.c
const char	*pwd(void);
int			cd(const char *path);
int			unset(t_data *data, char *name);
void		echo(char * str, char opt);
void		export(t_data *data, char *name, char *value);
void		display_list(t_list *lst);
void		exit_(t_data *data);

char	*find_var(t_data *data, char *var);

int		parse_cmd(t_data *data);
t_cmd	*cmdnew(char *content);
#endif
