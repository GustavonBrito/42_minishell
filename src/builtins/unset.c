/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:34 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/24 15:57:58 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(char **argv);

/**
 * @brief Implementa o comando 'unset'.
 *
 * Esta função remove variáveis de ambiente do ambiente atual do shell.
 * Percorre a lista de argumentos e para cada um, tenta remover a variável
 * de ambiente correspondente usando `unsetenv`.
 *
 * @param argv Um array de strings, onde argv é "unset" e os elementos
 *             subsequentes são os nomes das vars de ambiente a serem rm.
 */
void	unset(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
		unsetenv(argv[i++]);
}
