/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:31 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/24 15:57:50 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void);

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
