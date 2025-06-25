/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:34 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/24 22:21:44 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_command *cmd);

/**
 * @brief Implementa o comando 'unset'.
 *
 * Esta função remove variáveis de ambiente do ambiente atual do shell.
 * Percorre a estrutura `t_command`, e para cada um, tenta remover a variável
 * de ambiente correspondente usando `unsetenv`.
 *
 * @param cmd Estrutura contendo os argumentos e informações do comando 'unset'.
 */
void	unset(t_command *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i])
		unsetenv(cmd->args[i++]);
}
