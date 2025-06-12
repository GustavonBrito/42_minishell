/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:47:58 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/11 13:41:27 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void cd(char *argv)
{
	(void)argv;
	// chdir("Área de trabalho");
	// char *cwd = getcwd(NULL, 0);
	// ft_printf("%s", cwd);
	// if (chdir("/home/gustavo-linux") == -1)
    // {
    //     perror("chdir");
    //     return ;
    // }

    // char *cwd = getcwd(NULL, 0);
    // if (cwd)
    // {
    //     ft_printf("Diretório atual: %s\n", cwd);
    //     free(cwd);
    // }
	char 	**buffer;
	char 	*home;
	char	*actual_directory;
	
	buffer = ft_split(argv, ' ');
	if (buffer[1] == NULL)
	{
		home = malloc(sizeof(char) * ft_strlen(getenv("HOME")) + 1);
		ft_strlcpy(home, getenv("HOME"), ft_strlen(getenv("HOME") + 1));
		chdir(home);
		free(home);
	}
	if (chdir(buffer[1]) == -1)
	{
		ft_printf("No such file or directory: %s\n", buffer[1]);
		return ;
	}
	actual_directory = getcwd(NULL, 0);
	if (!actual_directory)
		return ;
	setenv("PWD", actual_directory, 1);
	free(actual_directory);
}
