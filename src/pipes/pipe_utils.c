/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:55:08 by luiza             #+#    #+#             */
/*   Updated: 2025/07/04 20:13:08 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FILE HAS NORMINETTE ERRORS -> NOTES B4 FTS WITH ERRORS

int		count_commands(t_command *cmd);
void	close_child(t_pipe *pipes);

/**
 * @brief Conta o número de comandos em uma lista encadeada de `t_command`.
 *
 * Percorre a lista de comandos e retorna a quantidade de elementos.
 *
 * @param cmd Ponteiro para o primeiro comando.
 * @return Número de comandos na lista.
 */

int	count_commands(t_command *cmd)
{
	int			count;
	t_command	*current;

	if (!cmd)
		return (0);
	count = 0;
	current = cmd;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/**
 * @brief Fecha o descritor de leitura do pipe anterior no filho.
 *
 * Utilizada no processo filho para fechar o FD de leitura herdado
 * antes de configurar os redirecionamentos e executar o comando.
 *
 * @param pipes APonteiro para a estrutura de controle de pipes.
 */

void	close_child(t_pipe *pipes)
{
	if (pipes->prev_pipe_read != 1)
		close(pipes->prev_pipe_read);
}
