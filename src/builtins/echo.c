/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:54:36 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/24 02:11:27 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Implementa o comando 'echo'.
 *
 * Esta função simula o comportamento do comando 'echo' do shell.
 * Ela imprime os args fornecidos para a saída padrão, separados por espaços.
 * Se nenhum argumento for fornecido, imprime uma nova linha.
 * Suporta a flag '-n' para suprimir a nova linha final.
 *
 * @param argv Um array de strings representando os args do comando 'echo',
 *             onde argv é "echo" e os elementos subsequentes são os argumentos
 *             a serem impressos.
 */
void	echo(char **argv)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (argv[1] == NULL)
	{
		ft_printf("\n");
		return ;
	}
	verify_flag(argv[1], &flag);
	if (flag)
		printf_without_n(argv);
	else
	{
		while (argv[++i])
		{
			if (i > 1)
				ft_printf(" ");
			ft_printf("%s", argv[i]);
		}
		ft_printf("\n");
	}
}
