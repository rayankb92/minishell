/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:26:47 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/01 11:40:54 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include "../libft/includes/libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

// typedef struct t_cmd{
// 	char	*cmd;
// 	char	*args;
// }

//	parse.c
int			check_quote(const char *str);
int			check_operateur(char *str);
int			is_in_charset(char c, char *charset);
int			error_msg(char *str);
int			check_chevrons(const char *str);

//	builtins.c
const char	*pwd(void);
int			cd(const char *path);
int			unset(char **env, char *name);
void		echo(char * str, char opt);
void		export(char **env, char *name, char *value);

#endif
