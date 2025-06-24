/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:43:27 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/24 15:56:19 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	verify_flag(char *argv_splited, int *flag);
void	printf_without_n(char **argv);

/**
 * @brief Verifica se um argumento de `echo` é a flag '-n'.
 *
 * Esta função analisa o primeiro argumento do comando `echo` para determinar
 * se ele é a flag `-n` (que suprime a nova linha).
 * A flag é reconhecida se for "-n" seguido de espaço, 'n' ou fim de string.
 *
 * @param argv_splited A str do arg a ser verificada (geralmente argv do echo).
 * @param flag Um ptr para um inteiro que será definido como 1 se a flag '-n'
 *        for encontrada e válida, e 0 caso contrário.
 */
void	verify_flag(char *argv_splited, int *flag)
{
	int	i;

	i = 0;
	if (argv_splited[0] == '-' && argv_splited[1] == 'n')
	{
		while (argv_splited[++i])
		{
			if (argv_splited[i + 1] == ' ' || argv_splited[i + 1] == 'n'
				|| argv_splited[i + 1] == '\0')
				*flag = 1;
			else
			{
				*flag = 0;
				break ;
			}
		}
	}
}

/**
 * @brief Imprime os argumentos do `echo` sem uma nova linha final.
 *
 * Esta função é usada pelo comando `echo` quando a flag '-n' está presente.
 * Ela itera pelos argumentos do `echo`, começando após a flag '-n', e os
 * imprime na saída padrão, sem adicionar uma nova linha ao final.
 *
 * @param argv Um array de strings, que são os argumentos do comando `echo`.
 *             Assume que a flag '-n' já foi tratada e os argumentos a serem
 *             impressos começam após ela.
 */
void	printf_without_n(char **argv)
{
	int	i;

	i = 1;
	while (1)
	{
		if (ft_strnstr(argv[i], "-n", ft_strlen(argv[i])) != 0)
			i++;
		else
		{
			ft_printf("%s", argv[i]);
			break ;
		}
	}
}
