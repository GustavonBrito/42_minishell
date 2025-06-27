/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:28 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/26 23:36:10 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FILE HAS NORMINETTE ERRORS -> NOTES B4 FTS WITH ERRORS

void	export(t_command *cmd);

/**
 * @brief Implementa o comando 'export'.
 *
 * Esta função manipula variáveis de ambiente.
 * Se chamada sem argumentos, comporta-se como `env` com o modo de exportação,
 * retornando env(1), ou seja, exibindo todas as vars de ambiente formatadas
 * com "declare -x".
 * Se argumentos forem fornecidos, verifica se cada argumento é do tipo
 * WORD (definido pela tokenização em `cmd->token_types`) e se contém um '=',
 * criando ou atualizando a variável de ambiente correspondente e
 * removendo aspas se necessário.
 *
 * @param cmd Estrutura contendo os argumentos e informações do comando.
 */

//norminette:+25 lines needs to be chopped
void	export(t_command *cmd)
{
	int		i;
	char	*key;
	char	*value;
	char	*equal_sign;

	if (!cmd->args[1])
	{
		env(1);
		return ;
	}
	i = 1;
	while (cmd->args[i])
	{
		if (cmd->token_types[i] == WORD)
		{
			equal_sign = ft_strchr(cmd->args[i], '=');
			if (equal_sign)
			{
				*equal_sign = '\0';
				key = cmd->args[i];
				value = equal_sign + 1;
				if ((value[0] == '"' && value[ft_strlen(value) - 1] == '"')
					|| (value[0] == '\'' && value[ft_strlen(value) - 1] == '\''))
				{
					value[ft_strlen(value) - 1] = '\0';
					value++;
				}
				setenv(key, value, 1);
				ft_printf("Created env %s\n", getenv(key));
				*equal_sign = '=';
			}
		}
		i++;
	}
}
