/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:48:57 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/21 17:46:02 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
 #include <dirent.h>

// void	ft_wildcard(t-data *data, char **clean)
// {
// 	int i;

// 	i = 0;
// 	while (clean[i])
// 	{
// 		if (ft_strchr('*', clean[i]))
// 			handle_
// 	}
// }

void	copy_files(char *find, t_data *data)
{
	DIR				*d;
	struct dirent	*dir;
	int				i;

	i = 0;
	d = opendir(".");
	if (!d)
		return ;
	if (ft_strcmp(find, "*") == 0)
	{
		ft_printf("la\n");
	}

	while ((dir = readdir(d)))
		ft_lstadd_back(&data->dir, ft_lstnew(ft_strdup(dir->d_name)));
	closedir(d);
	display_lst(data->dir);
}

int list_dir(void)
{
	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	dir = readdir(d);
	if (d)
	{
		printf("FILENAME: %s\n", dir->d_name);
		dir = readdir(d);
		printf("FILENAME: %s\n", dir->d_name);
		dir = readdir(d);
		printf("FILENAME: %s\n", dir->d_name);
		dir = readdir(d);
		printf("FILENAME: %s\n", dir->d_name);

		closedir(d);
	}
	return(0);
}