/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 06:28:59 by luiza             #+#    #+#             */
/*   Updated: 2025/06/24 17:36:06 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		report_error(const char *msg, int exit_code);
void	critical_error(const char *msg, int exit_code);

/**
 * @brief Reporta uma mensagem de erro e retorna um código de saída.
 *
 * Imprime a mensagem de erro formatada para a saída padrão de erros
 * (assumindo ft_printf).
 * Não encerra o programa, apenas retorna o código de saída especificado.
 *
 * @param msg A mensagem de erro a ser exibida.
 * @param exit_code O código de saída a ser retornado.
 * @return O `exit_code` fornecido.
 */
int	report_error(const char *msg, int exit_code)
{
	ft_printf("minishell: %s\n", msg);
	return (exit_code);
}

/**
 * @brief Reporta um erro crítico e encerra o programa.
 *
 * Imprime a mensagem de erro formatada para a saída padrão de erros e,
 * encerra o programa imediatamente com o código de saída especificado.
 *
 * @param msg A mensagem de erro crítico a ser exibida.
 * @param exit_code O código de saída com o qual o programa será encerrado.
 */
void	critical_error(const char *msg, int exit_code)
{
	ft_printf("minishell: %s\n", msg);
	exit(exit_code);
}
