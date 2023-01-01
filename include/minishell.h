/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:26:47 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/01 02:03:40 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include "../libft/includes/libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct t_data{
	char	**env;
	char	*entry;
}				t_data;

//	parse.c
int			check_quote(char *str);
int			check_operateur(char *str);
int			is_in_charset(char c, char *charset);
int			error_msg(char *str);
int			check_chevrons(const char *str);

//	builtins.c
const char	*pwd(void);
void		echo(char * str, char opt);
int			cd(const char *path);
void		export(char **env, char *name, char *value);
int			unset(char **env, char *name);
int			unset(char **env, char *name);
#endif
