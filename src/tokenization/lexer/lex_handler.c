/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:21:55 by luiza             #+#    #+#             */
/*   Updated: 2025/07/22 20:01:15 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			handle_quotes(char *input, t_token **token_lst, int i);
int			handle_var(char *input, t_token **token_lst, int i);
//static int	process_quote(char *input, t_token **token_lst, int start,
//				char quote_type);
static int	process_var_name(char *input, t_token **token_lst, int start);
static int	handle_special_vars(char *input, t_token **token_lst, int i);
int			handle_word_with_quotes(char *input, t_token **token_lst, int i);

/**
 * @brief Lida com a tokenização de strings entre aspas.
 *
 * Esta função é responsável por encontrar o fechamento de uma
 * aspa (simples ou dupla), extrair o conteúdo entre aspas e criar um
 * token apropriado (`SINGLE_QUOTE` ou `DOUBLE_QUOTE`).
 * Reporta um erro de sintaxe se a aspa não for fechada.
 *
 * @param input A string de entrada completa.
 * @param token_lst Um ponteiro para a lista de tokens onde o novo token
 *        será adicionado.
 * @param i O índice atual na string de entrada onde a aspa de abertura foi
 *          encontrada.
 * @return O número de caracteres processados (comprimento da string entre
 *         aspas + 2 para aspas), ou 1 em caso de erro de aspas não fechadas.
 */
int	handle_quotes(char *input, t_token **token_lst, int i)
{
	char	quote_char;
	int		start;
	int		j;
	char	*quoted_content;
	int		len;
	int		quote_count;
	int		temp_j;

	quote_char = input[i];
	start = i;
	j = i + 1;
	while (input[j])
	{
		if (input[j] == quote_char)
		{
			if (quote_char == '"')
			{
				quote_count = 1;
				temp_j = j + 1;
				while (input[temp_j] && input[temp_j] != ' ' && input[temp_j] != '|')
				{
					if (input[temp_j] == '"')
						quote_count++;
					temp_j++;
				}
				if (quote_count % 2 == 0)
					break ;
			}
			else
				break ;
		}
		j++;
	}
	if (input[j] != quote_char)
		return (1);
	j++;
	len = j - start;
	quoted_content = ft_substr(input, start, len);
	if (!quoted_content)
		return (len);
	if (quote_char == '\'')
		add_token(token_lst, quoted_content, SINGLE_QUOTE);
	else
		add_token(token_lst, quoted_content, DOUBLE_QUOTE);
	free(quoted_content);
	return (len);
}

/**
 * @brief Lida com a tokenização de variáveis.
 *
 * Esta função é chamada quando um caractere '$' é encontrado. Ela determina
 * se é uma variável especial (`$?` ou `$$`) ou uma var de ambiente normal,
 * e então chama a função auxiliar apropriada para criar o token `VAR`.
 * Se o '$' não for seguido por um nome de variável válido, é tratado como
 * uma palavra literal.
 *
 * @param input A string de entrada completa.
 * @param token_lst Um ponteiro para a lista de tokens onde o novo token
 *        será adicionado.
 * @param i O índice atual na string de entrada onde o '$' foi encontrado.
 * @return O número de caracteres processados para formar o token da variável.
 */
int	handle_var(char *input, t_token **token_lst, int i)
{
	int	start;

	start = i;
	i++;
	if (input[i] == '?' || input[i] == '$')
		return (handle_special_vars(input, token_lst, i - 1));
	if (!ft_isalpha(input[i]) && input[i] != '_')
	{
		add_token(token_lst, "$", WORD);
		return (1);
	}
	return (process_var_name(input, token_lst, start));
}

/**
 * @brief Processa o conteúdo de uma string entre aspas.
 *
 * Extrai a substring entre as aspas e a adiciona à lista de tokens
 * como um token `SINGLE_QUOTE` ou `DOUBLE_QUOTE`, dependendo do tipo de aspa.
 *
 * @param input A string de entrada completa.
 * @param token_lst Um ponteiro para a lista de tokens.
 * @param start O índice de início do conteúdo da citação
 *        (após a aspa de abertura).
 * @param quote_type O caractere da aspa ('\'' ou '"').
 * @return O número de caracteres processados, incluindo as aspas.
 */
/* static int	process_quote(char *input, t_token **token_lst, int start
	, char quote_type)
{
	int		i;
	int		len;
	char	*content;

	i = start;
	while (input[i] && input[i] != quote_type)
		i++;
	len = i - start;
	content = ft_substr(input, start, len);
	if (!content)
		return (len + 2);
	if (quote_type == '\'')
	{
		add_token(token_lst, content, SINGLE_QUOTE);
	}
	else
	{
		add_token(token_lst, content, DOUBLE_QUOTE);
	}
	free(content);
	return (len + 2);
} */

/**
 * @brief Processa o nome de uma variável de ambiente.
 *
 * Extrai o nome da variável (seguindo as regras de nomes de vars de shell:
 * alfanum ou underscore) e a adiciona à lista de tokens como um token `VAR`.
 *
 * @param input A string de entrada completa.
 * @param token_lst Um ponteiro para a lista de tokens.
 * @param start O índice de início do `$VAR` (incluindo o '$').
 * @return O número de chars processados para o nome da var (incluindo o '$').
 */
static int	process_var_name(char *input, t_token **token_lst, int start)
{
	int		i;
	int		len;
	char	*var_name;

	i = start + 1;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		i++;
	len = i - start;
	var_name = ft_substr(input, start, len);
	if (!var_name)
		return (len);
	add_token(token_lst, var_name, VAR);
	free(var_name);
	return (len);
}

/**
 * @brief Lida com variáveis especiais como `$?` e `$$`.
 *
 * Verifica se o caractere após o '$' é '?' ou '$' e cria o token `VAR`
 * apropriado para `$?` ou `$$`.
 *
 * @param input A string de entrada completa.
 * @param token_lst Um ponteiro para a lista de tokens.
 * @param i O índice do caractere '$' na string de entrada.
 * @return O número de caracteres processados (2 para `$?` ou `$$`, 1 para
 *        '$' literal).
 */
static int	handle_special_vars(char *input, t_token **token_lst, int i)
{
	if (input[i + 1] == '?')
	{
		add_token(token_lst, "$?", VAR);
		return (2);
	}
	if (input[i + 1] == '$')
	{
		add_token(token_lst, "$$", VAR);
		return (2);
	}
	return (1);
}

int	handle_word_with_quotes(char *input, t_token **token_lst, int i)
{
	int		start;
	int		j;
	char	*full_word;
	int		len;
	char	quote_char;

	start = i;
	j = i;
	while (input[j] && !ft_isspace(input[j]) && !ft_isop(input[j]) && input[j] != '$')
	{
		if (input[j] == '\'' || input[j] == '"')
		{
			quote_char = input[j];
			j++;
			while (input[j] && input[j] != quote_char)
				j++;
			if (input[j] == quote_char)
				j++;
		}
		else
			j++;
	}
	len = j - start;
	full_word = ft_substr(input, start, len);
	if (!full_word)
		return (len);

	add_token(token_lst, full_word, WORD);
	free(full_word);
	return (len);
}
