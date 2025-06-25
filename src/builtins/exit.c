/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:26 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/24 15:57:26 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell(void);

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
