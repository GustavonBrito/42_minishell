/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:26 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/22 20:52:09 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Implementa o comando 'exit'.
 *
 * Esta função encerra a execução do programa minishell.
 * Atualmente, sempre sai com o status de sucesso (0).
 */
void	exit_minishell(void)
{
	exit(0);
}
