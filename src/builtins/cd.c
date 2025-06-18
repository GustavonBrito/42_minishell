/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:47:58 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/17 19:31:24 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void cd(char *argv, t_token *token_lst)
{
	//char 	**buffer;
	char 	*home;
	char	*actual_directory;
	
	(void) argv;
	// buffer = ft_split(argv, ' ');
	// if (buffer[1] == NULL)
	// {
	// 	home = malloc(sizeof(char) * ft_strlen(getenv("HOME")) + 1);
	// 	ft_strlcpy(home, getenv("HOME"), ft_strlen(getenv("HOME") + 1));
	// 	chdir(home);
	// 	free(home);
	// }
	// if (chdir(buffer[1]) == -1)
	// {
	// 	ft_printf("No such file or directory: %s\n", buffer[1]);
	// 	return ;
	// }
	if (token_lst->next != NULL)
	{
		if (chdir(token_lst->next->value) == -1)
		{
			ft_printf("No such file or directory: %s\n", token_lst->next->value);
			return ;
		}
	}
	if (token_lst->next == NULL)
	{
		home = malloc(sizeof(char) * ft_strlen(getenv("HOME")) + 1);
		ft_strlcpy(home, getenv("HOME"), ft_strlen(getenv("HOME")) + 1);
		chdir(home);
		free(home);
	}
	actual_directory = getcwd(NULL, 0);
	if (!actual_directory)
		return ;
	setenv("PWD", actual_directory, 1);
	free(actual_directory);
}
