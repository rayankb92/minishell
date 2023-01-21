/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 08:06:30 by jewancti          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/01/21 18:15:17 by jewancti         ###   ########.fr       */
=======
/*   Updated: 2023/01/20 01:44:47 by rferradi         ###   ########.fr       */
>>>>>>> refs/remotes/origin/main
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_key_from_tenv(t_env *tenv, const char *key)
{
	t_env	*tmp;

	tmp = tenv;
	while (tmp)
	{
		if (tmp -> key && ft_strcmp(tmp -> key, key) == 0)
			return (tmp -> value);
		tmp = tmp -> next;
	}
	return (NULL);
}

void	set_path_from_tenv(t_data *data)
{
	char	*temp;

	temp = get_key_from_tenv(data -> tenv, "PATH");
	if (temp && !data -> path)
		data -> path = ft_split(temp, ':');
}

void	update_status_code(t_data *data, short code)
{
	char	*temp;
	char	*to_string;

	temp = ft_strdup("?=");
	to_string = ft_itoa(code);
	ft_realloc(& temp, to_string);
	export(data, temp, 1);
	ft_memdel((void **)& temp);
	ft_memdel((void **)& to_string);
}
