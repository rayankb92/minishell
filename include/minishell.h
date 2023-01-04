/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:26:47 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/04 16:52:32 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include "libft.h"

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

	const char	*suite_args;
	int			args_is_specified;
}	t_sequence;

typedef struct s_cmd
{
	char			*command;
	char			*args;
	
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

//	parse.c
int			check_quote(const char *str);
int			check_operateur(char *str);
int			is_in_charset(char c, char *charset);
int			error_msg(char *str);
int			check_chevrons(const char *str);
void		set_data(char **env, t_data *data);

//	builtins.c
const char	*pwd(void);
int			cd(const char *path);
int			unset(t_data *data, char *name);
void		echo(char * str, char opt);
void		export(t_data *data, char *name, char *value);
void		display_list(t_list *lst);
void		exit_(t_data *data);

//	signal.c
void		ctrlc(int sig);
//	dir: interpret_input
//	int
void		interpret_input(const char *input);
void		is_exit(const char *entry);
//	print.c
void		print_cmd(t_cmd *cmd);

int		parse_cmd(t_data *data);
t_cmd	*cmdnew(char *content);
#endif
