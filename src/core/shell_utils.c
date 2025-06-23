/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 23:07:58 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/22 21:24:51 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_exit_condition(char *buffer_received);
void	signal_handler(int signal);

/**
 * @brief Verifica a condição de saída do shell.
 *
 * Esta função verifica se o buffer de entrada recebido é NULL, o que geralmente
 * indica que o usuário pressionou Ctrl+D (EOF). Se for NULL, imprime "exit"
 * e encerra o programa.
 *
 * @param buffer_received A string lida pelo readline.
 */
void	check_exit_condition(char *buffer_received)
{
	if (buffer_received == NULL)
	{
		ft_printf("exit\n");
		exit(0);
	}
}

/**
 * @brief Manipulador de sinais para o shell.
 *
 * Lida com o sinal `SIGINT` (Ctrl+C). Quando o sinal é recebido,
 * ele imprime uma nova linha, limpa a linha atual do readline,
 * redesenha o prompt e define o status de saída global para 130.
 * O parâmetro `signal` é `(void)` pois não é usado diretamente na função.
 *
 * @param signal O número do sinal recebido.
 */
void	signal_handler(int signal)
{
	(void)signal;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}
