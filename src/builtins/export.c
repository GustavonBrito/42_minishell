/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:28 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/07 00:56:41 by gustavo-lin      ###   ########.fr       */
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
	t_env	*s_env;
	char	**buffer_input;
	char	**buffer_from_env;
	int		i;

	i = 0;
	if (argv[1] == NULL)
		env(1);
	else
	{
		buffer_input = ft_split(argv[1], '=');
		s_env = get_t_env();
		while(s_env)
		{
			buffer_from_env = ft_split(s_env->env_data, '=');
			if (ft_strncmp(buffer_from_env[0], buffer_input[0], ft_strlen(buffer_input[0])) == 0)
			{
				s_env->env_data = ft_strdup(argv[1]);
				return ;
			}
			if (s_env->next == NULL)
			{
				ft_printf("%s\n", argv[++i]);
				while (argv[++i])
				{
					s_env->next = malloc(sizeof(t_env));
					s_env = s_env->next;
					s_env->env_data = ft_strdup(argv[i]);
					s_env->next = NULL;
				}
			}
			s_env = s_env->next;
		}
	}
}
