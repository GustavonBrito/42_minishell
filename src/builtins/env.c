/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/11 22:02:04 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FILE HAS NORMINETTE ERRORS -> NOTES B4 FTS WITH ERRORS

void	env(int is_export);
void	print_export(void);


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
	t_env	**env_ptr;
	t_env	*env;

	if (is_export == 1)
		print_export();
	else
	{
		env_ptr = handle_t_env(NULL);
		env = *env_ptr;
		while(env)
		{
			ft_printf("%s\n", env->env_data);
			env = env->next;
		}
	}
}

/**
 * @brief Imprime as vars de ambiente formatadas para o cmd 'export' sem args.
 *
 * Esta função itera sobre o array global `environ` e imprime cada variável
 * de ambiente no formato `declare -x CHAVE="VALOR"`. Variáveis sem valor
 * são impressas como `declare -x CHAVE`.
 * A função percorre e imprime as variáveis que começam com:
 * 1) letras maiúsculas; 2) letras minúsculas; 3)antes de imprimir as demais.
 */

//norminette: many vars and +25 lines: needs to be chopped
void	print_export(void)
{
	t_env		*env;
	char		**buffer;

	env = *handle_t_env(NULL);
	while (env)
	{
		buffer = ft_split(env->env_data, '=');
		if (buffer[1] == NULL)
			ft_printf("declare -x %s\n", buffer[0]);
		else
			ft_printf("declare -x %s=\"%s\"\n", buffer[0], buffer[1]);
		ft_free_split(buffer);
		env = env->next;
	}
}
