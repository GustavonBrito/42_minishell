/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/06 23:50:40 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Imprime as variáveis de ambiente formatadas para o comando 'export' sem argumentos.
 *
 * Esta função itera sobre o array global `environ` e imprime cada variável
 * de ambiente no formato `declare -x CHAVE="VALOR"`. Variáveis sem valor
 * são impressas como `declare -x CHAVE`.
 * A lógica tenta ordenar as variáveis com base no primeiro caractere (letras maiúsculas e minúsculas)
 * antes de imprimir aquelas que não começam com letras.
 */
void	print_export(void)
{
	extern char	**environ;
	char		**buffer;
	int			i;
	int			is_upper_char;
	int			is_lower_char;
	char		*temp;

	temp = malloc(sizeof(char) * 2);
	is_upper_char = 64;
	is_lower_char = 96;
	while (++is_upper_char <= 90 && ++is_lower_char <= 122)
	{
		i = -1;
		while (environ[++i])
		{
			ft_strlcpy(temp, environ[i], 2);
			if (temp[0] == is_upper_char || temp[0] == is_lower_char)
			{
				buffer = ft_split(environ[i], '=');
				if (buffer[1] == NULL)
					ft_printf("declare -x %s\n", buffer[0]);
				else
					ft_printf("declare -x %s=\"%s\"\n", buffer[0], buffer[1]);
			}
		}
	}
	i = -1;
	while (environ[++i])
	{
		ft_strlcpy(temp, environ[i], 2);
		if (ft_isalpha(temp[0]) == 0)
		{
			buffer = ft_split(environ[i], '=');
			if (buffer[1] == NULL)
				ft_printf("declare -x %s\n", buffer[0]);
			else
				ft_printf("declare -x %s=\"%s\"\n", buffer[0], buffer[1]);
		}
	}
}

/**
 * @brief Implementa o comando 'env'.
 *
 * Esta função exibe as variáveis de ambiente.
 * Se `is_export` for 1, chama `print_export` para um formato detalhado
 * (usado pelo comando 'export' sem argumentos). Caso contrário, imprime
 * cada variável de ambiente em uma nova linha.
 *
 * @param is_export Um flag booleano (0 ou 1) que determina o formato de saída.
 *                  1 para o formato `declare -x` (como 'export' sem args),
 *                  0 para o formato padrão do 'env'.
 */
void	env(int is_export)
{
	t_env		*env;

	if (is_export == 1)
		print_export();
	else
	{
		env = handle_t_env(NULL);
		while(env)
		{
			ft_printf("%s\n", env->env_data);
			env = env->next;
		}
	}
}
