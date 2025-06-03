/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:54:36 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/02 22:47:36 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void echo(char *argv)
{
	t_builtins *builtins;

	builtins = (t_builtins *)malloc(sizeof(t_builtins));
	builtins->flag = 0;
	builtins->name = "echo";
	verify_flag(argv, &builtins);
	printf("Flag: %d", builtins->flag);
}
// parei implementando a funcao de echo com ou sem flag -n



// Resumo do funcionamento
// Recebe os argumentos: O texto e as opções são passados para o programa.
// Processa as opções: Ajusta o comportamento com base em -n, -e, etc.
// Interpreta caracteres especiais: Se necessário, converte \n, \t, etc.
// Escreve na saída padrão: Usa chamadas de sistema para imprimir no terminal.
// Adiciona nova linha: Por padrão, adiciona uma nova linha ao final da saída.