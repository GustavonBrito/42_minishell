/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:43:27 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/25 01:19:33 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify_flag(char *arg);

/**
 * @brief Verifica se um argumento de `echo` é a flag '-n' e se válida.
 *
 * Esta função analisa o primeiro argumento do comando `echo` para determinar
 * se ele é a flag `-n` (que suprime a nova linha).
 * A flag é reconhecida se for "-n" seguido de espaço, 'n' ou fim de string.
 *
 * @param arg A string do argumento a ser verificada.
 * @return 1 se for uma flag '-n' válida, 0 caso contrário.
 */
int	verify_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 1;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}
