/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:45:31 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/06 23:14:32 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;
int	main(int argc, char **argv, char **env);

/**
 * @brief A função principal do programa minishell.
 *
 * Inicializa o status de saída global (`g_exit_status`) e, em seguida,
 * entra no loop principal do shell (`shell_loop`) para começar a processar
 * comandos.
 *
 * @return 0 ao sair do programa.
 */
int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	g_exit_status = 0;
	handle_store_env(env);
	shell_loop();
	return (0);
}
