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

void	exit_minishell(char *exit_code);

/**
 * @brief Implementa o comando 'exit'.
 *
 * Esta função encerra a execução do programa minishell.
 * Atualmente, sempre sai com o status de sucesso (0).
 */
void	exit_minishell(char *exit_code)
{
	int exit_code_converted;
	
	exit_code_converted = ft_atoi(exit_code);
	if (exit_code_converted == 0)
		ft_printf("%s", exit_code);
	exit(exit_code_converted);
}
