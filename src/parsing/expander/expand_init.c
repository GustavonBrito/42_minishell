/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:03:33 by luiza             #+#    #+#             */
/*   Updated: 2025/06/22 21:12:40 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				expand_variables(t_command *cmd);
char			*expand_str(const char *str, int expand_check);
int				handle_dollar_expansion(const char *str, char **res, int i_cmd);
static int		handle_lone_dollar(char **res);

/**
 * @brief Expande variáveis em todos os argumentos de um comando.
 *
 * Esta função itera por cada argumento da estrutura `t_command` e,
 * se o token não for uma aspas simples, chama `expand_str` para
 * realizar a expansão de variáveis. O argumento original é liberado
 * e substituído pela string expandida.
 *
 * @param cmd Um ponteiro para a estrutura `t_command` cujos argumentos serão expandidos.
 * @return 0 em caso de sucesso, ou 1 em caso de erro de alocação de memória.
 */
int	expand_variables(t_command *cmd)
{
	int		i;
	char	*expand;
	int		expand_check;

	i = 0;
	while (cmd->args[i])
	{
		expand_check = (cmd->token_types && cmd->token_types[i]
				!= SINGLE_QUOTE);
		expand = expand_str(cmd->args[i], expand_check);
		if (!expand)
			return (report_error("memory allocation error", 1));
		free(cmd->args[i]);
		cmd->args[i] = expand;
		i++;
	}
	return (0);
}

/**
 * @brief Expande variáveis dentro de uma única string.
 *
 * Percorre a string de entrada caractere por caractere. Se encontrar um '$'
 * e `expand_check` for verdadeiro (ou seja, não estamos dentro de aspas simples),
 * chama `handle_dollar_expansion`. Caso contrário, trata o caractere como normal.
 * Constrói a string expandida incrementalmente.
 *
 * @param str A string de entrada possivelmente contendo variáveis a serem expandidas.
 * @param expand_check Um flag booleano (0 ou 1) que indica se a expansão de variáveis
 *                     deve ocorrer (1) ou ser ignorada (0, e.g., dentro de aspas simples).
 * @return Uma nova string com as variáveis expandidas, ou NULL em caso de erro de alocação.
 */
char	*expand_str(const char *str, int expand_check)
{
	char	*res;
	int		i_cmd;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	i_cmd = 0;
	while (str[i_cmd])
	{
		if (str[i_cmd] == '$' && expand_check)
			i_cmd += handle_dollar_expansion(str, &res, i_cmd);
		else
			i_cmd += handle_regular_char(str, &res, i_cmd);
		if (!res)
			return (NULL);
	}
	return (res);
}

/**
 * @brief Lida com a expansão de diferentes tipos de variáveis precedidas por '$'.
 *
 * Analisa o caractere seguinte ao '$' para determinar o tipo de expansão:
 * - `$?`: status de saída do último comando.
 * - `$$`: ID do processo atual.
 * - `$` seguido por letra ou '_' : variável de ambiente.
 * - `$`: Tratado como um caractere literal se não corresponder a nenhum dos acima.
 *
 * @param str A string de entrada onde o '$' foi encontrado.
 * @param res Um ponteiro para a string de resultado onde a expansão será anexada.
 * @param i_cmd O índice atual na string de entrada onde o '$' foi encontrado.
 * @return O número de caracteres processados a partir de `i_cmd` (incluindo o '$').
 */
int	handle_dollar_expansion(const char *str, char **res, int i_cmd)
{
	i_cmd++;
	if (str[i_cmd] == '?')
		return (expand_exit_status(res) + 1);
	else if (str[i_cmd] == '$')
		return (expand_process_id(res) + 1);
	else if (str[i_cmd] && (ft_isalpha(str[i_cmd]) || str[i_cmd] == '_'))
		return (expand_env_var(str, res, i_cmd) + 1);
	else
		return (handle_lone_dollar(res));
}

/**
 * @brief Lida com a expansão de diferentes tipos de variáveis precedidas por '$'.
 *
 * Analisa o caractere seguinte ao '$' para determinar o tipo de expansão:
 * - `$?`: status de saída do último comando.
 * - `$$`: ID do processo atual.
 * - `$` seguido por letra ou '_' : variável de ambiente.
 * - `$`: Tratado como um caractere literal se não corresponder a nenhum dos acima.
 *
 * @param str A string de entrada onde o '$' foi encontrado.
 * @param res Um ponteiro para a string de resultado onde a expansão será anexada.
 * @param i_cmd O índice atual na string de entrada onde o '$' foi encontrado.
 * @return O número de caracteres processados a partir de `i_cmd` (incluindo o '$').
 */
static int	handle_lone_dollar(char **res)
{
	*res = append_char(*res, '$');
	if (!*res)
		return (0);
	return (1);
}
