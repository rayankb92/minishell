/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:26:47 by rferradi          #+#    #+#             */
/*   Updated: 2022/12/30 06:58:53 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

// typedef struct t_cmd{
// 	char	*cmd;
// 	char	*args;
// }

int	check_quote(char *str);
int	check_operateur(char *str);
int	is_in_charset(char c, char *charset);
int	error_msg(char *str);


