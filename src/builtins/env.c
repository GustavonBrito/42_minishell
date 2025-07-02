/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/02 01:32:12 by gustavo-lin      ###   ########.fr       */
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
	extern char	**environ;
	int			i;

	i = -1;
	if (is_export == 1)
		print_export();
	else
	{
		while (environ[++i])
			ft_printf("%s\n", environ[i]);
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
	ft_free_split(buffer);
	free(temp);
}
