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

void echo(char *argv, t_builtins **builtins)
{
	int i;
	char **buffer;
	
	i = 0;
	buffer = ft_split(argv, ' ');
	if (buffer[1] == NULL)
	{
		printf("\n");
		return ;
	}
	else
		verify_flag(buffer[1], builtins);
	if ((*builtins)->flag == 1)
		printf_without_n(buffer); //Parei aqui, implementar essa funcao sem o \n
	else
	{
		while (buffer[++i])
		{
			if (i >= 2)
				printf(" ");
			printf("%s", buffer[i]);
		}
		printf("\n");
	}
}

// Resumo do funcionamento
// Recebe os argumentos: O texto e as opções são passados para o programa.
// Processa as opções: Ajusta o comportamento com base em -n.
// Escreve na saída padrão: Usa chamadas de sistema para imprimir no terminal.
// Adiciona nova linha: Por padrão, adiciona uma nova linha ao final da saída.