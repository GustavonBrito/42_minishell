/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:59:26 by luiza             #+#    #+#             */
/*   Updated: 2025/06/24 17:40:09 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		update_pwd(void);

/**
 * @brief Atualiza a variável de ambiente PWD.
 *
 * Obtém o diretório de trabalho atual via getcwd e atualiza a variável
 * de ambiente PWD com esse valor usando setenv. Libera a memória alocada
 * após a atualização.
 */

void	update_pwd(void)
{
	char	*actual_directory;

	actual_directory = getcwd(NULL, 0);
	if (!actual_directory)
		return ;
	setenv("PWD", actual_directory, 1);
	free(actual_directory);
}
