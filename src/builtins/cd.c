/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:47:58 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/10 19:50:31 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cd(char *argv)
{
	char **buffer;
	char *actual_directory;

	buffer = ft_split(argv, ' ');
	if (chdir(buffer[1]) == -1)
	{
		printf("No such file or directory: %s\n", buffer[1]);
		return ;
	}
	actual_directory = getcwd(NULL, 0);
	if (!actual_directory)
		free(actual_directory);
	setenv("PWD", actual_directory, 1);
	free(actual_directory);
}
