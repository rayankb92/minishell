/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:26:47 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/02 00:12:42 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include "../libft/includes/libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct t_data{
	t_list	        *env;
	struct s_lst    *next;
}               t_data;

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
void		display_list(t_list *lst);
void		exit_(t_data *data);
#endif
