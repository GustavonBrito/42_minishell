/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:47:58 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/07 21:49:29 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Implementa o comando 'cd'.
 *
 * Esta função muda o diretório de trabalho atual do shell.
 * Se nenhum argumento for fornecido, tenta mudar para o diretório HOME do usuário.
 * Se um argumento for fornecido, tenta mudar para o diretório especificado.
 * Em caso de sucesso, atualiza a variável de ambiente PWD.
 * Reporta erros se o diretório HOME não estiver definido ou se o diretório de destino
 * não existir ou não puder ser acessado.
 *
 * @param argv Um array de strings, onde argv é "cd" e argv (se existir)
 *             é o caminho para o diretório de destino.
 */
void	cd(char **argv)
{
	char	*home;
	char	*actual_directory;
	char	*target_dir;

	if (!argv[1])
	{
		home = getenv("HOME");
		if (!home)
		{
			ft_printf("cd: HOME not set\n");
			return ;
		}
		chdir(home);
		return;
	}
	else
		target_dir = argv[1];
	if (chdir(argv[1]) == -1)
	{
		ft_printf("No such file or directory: %s\n", target_dir);
		return ;
	}
	actual_directory = getcwd(NULL, 0);
	if (!actual_directory)
		return ;
	setenv("PWD", actual_directory, 1);
	free(actual_directory);
}
