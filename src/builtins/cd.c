/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:47:58 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/06 13:19:50 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//int chdir(const char *path)
void cd(char *argv, t_builtins **builtins)
{
	(void) builtins;
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

// Observações importantes

// chdir() retorna -1 em caso de erro → você deve tratar isso.

// getcwd() te dá o caminho real após o cd (resolvendo .., . etc).

// setenv() atualiza as variáveis visíveis no shell.

//	char *getenv(const char *name);