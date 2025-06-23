/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:31 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/22 20:50:40 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Implementa o comando 'pwd'.
 *
 * Esta função imprime o diretório de trabalho atual para a saída padrão.
 * Obtém o diretório diretamente da variável de ambiente "PWD".
 */
void	pwd(void)
{
	ft_printf("%s\n", getenv("PWD"));
}
