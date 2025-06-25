/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:03:33 by luiza             #+#    #+#             */
/*   Updated: 2025/06/24 01:43:04 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_str(char *dest, const char *src);
char	*get_env_val(const char *var_name);
char	*append_char(char *dest, char c);
int		handle_regular_char(const char *str, char **res, int i);

/**
 * @brief Concatena uma string de origem a uma string de destino, realocando
 * conforme necessário.
 *
 * Esta função cria uma nova string que é a concatenação de `dest` e `src`.
 * A memória da string `dest` original é liberada.
 *
 * @param dest A string de destino (será liberada).
 * @param src A string de origem a ser anexada.
 * @return Uma nova string com o conteúdo concatenado, ou NULL em caso de erro
 *         de alocação.
 */
char	*append_str(char *dest, const char *src)
{
	char	*new_str;
	size_t	new_len;

	if (!dest || !src)
		return (NULL);
	new_len = ft_strlen(dest) + ft_strlen(src);
	new_str = malloc(new_len + 1);
	if (!new_str)
		return (NULL);
	new_str[0] = '\0';
	ft_strlcat(new_str, dest, new_len + 1);
	ft_strlcat(new_str, src, new_len + 1);
	free(dest);
	return (new_str);
}

/**
 * @brief Obtém o valor de uma variável de ambiente.
 *
 * Esta função usa `getenv` para buscar o valor de uma variável de ambiente.
 * Se a variável não for encontrada, retorna uma string vazia duplicada.
 * Caso contrário, retorna uma cópia duplicada do valor encontrado.
 *
 * @param var_name O nome da variável de ambiente.
 * @return Uma nova string contendo o valor da variável, ou uma string vazia
 *         se a var não for definida. Retorna NULL em caso de erro de alocação.
 */
char	*get_env_val(const char *var_name)
{
	char	*value;

	value = getenv(var_name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

/**
 * @brief Anexa um único char a uma string, realocando conforme necessário.
 *
 * Esta função cria uma nova string que contém o conteúdo original de `dest`
 * seguido pelo caractere `c`. A memória da string `dest` original é liberada.
 *
 * @param dest A string de destino (será liberada).
 * @param c O caractere a ser anexado.
 * @return Uma nova string com o char anexado, ou NULL em caso de erro.
 */
char	*append_char(char *dest, char c)
{
	char	*new_str;
	size_t	len;

	if (!dest)
		return (NULL);
	len = ft_strlen(dest);
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	new_str[0] = '\0';
	ft_strlcat(new_str, dest, len + 2);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(dest);
	return (new_str);
}

/**
 * @brief Lida com caracteres que não são parte de uma expansão de variável.
 *
 * Simplesmente anexa o char atual da string de entrada à string de resultado.
 *
 * @param str A string de entrada.
 * @param res Um ponteiro para a string de resultado onde o char será anexado.
 * @param i O índice do caractere atual em `str`.
 * @return 1 se o caractere foi anexado com sucesso, 0 em caso de falha.
 */
int	handle_regular_char(const char *str, char **res, int i)
{
	*res = append_char(*res, str[i]);
	if (!*res)
		return (0);
	return (1);
}
