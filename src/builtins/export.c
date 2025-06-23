/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:28 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/22 20:50:25 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Implementa o comando 'export'.
 *
 * Esta função manipula variáveis de ambiente.
 * Se chamada sem argumentos, comporta-se como `env` com o modo de exportação,
 * exibindo todas as variáveis de ambiente formatadas com "declare -x".
 * Se um argumento `CHAVE=VALOR` for fornecido, cria ou atualiza a variável
 * de ambiente correspondente.
 *
 * @param argv Um array de strings, onde argv é "export" e argv (se existir)
 *             é a variável de ambiente a ser exportada no formato "CHAVE=VALOR".
 */
void	export(char **argv)
{
	char	**sub_buffer;

	if (argv[1] == NULL)
		env(1);
	else
	{
		sub_buffer = ft_split(argv[1], '=');
		setenv(sub_buffer[0], sub_buffer[1], 1);
		ft_printf("Created env %s\n", getenv(sub_buffer[0]));
	}
}
