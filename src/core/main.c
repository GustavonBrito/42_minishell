/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:45:31 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/22 21:25:32 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

/**
 * @brief A função principal do programa minishell.
 *
 * Inicializa o status de saída global (`g_exit_status`) e, em seguida,
 * entra no loop principal do shell (`shell_loop`) para começar a processar
 * comandos.
 *
 * @return 0 ao sair do programa.
 */
int	main(void)
{
	g_exit_status = 0;
	shell_loop();
	return (0);
}
