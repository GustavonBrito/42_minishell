/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:03:33 by luiza             #+#    #+#             */
/*   Updated: 2025/06/24 01:40:51 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		expand_exit_status(char **res);
char	*itoa_exit_status(void);
int		expand_process_id(char **res);
char	*itoa_process_id(void);
int		expand_env_var(const char *str, char **res, int i_cmd);

/**
 * @brief Expande a variável especial `$?` para o status de saída global.
 *
 * Converte o valor de `g_exit_status` para uma string e anexa à string de
 * resultado.
 *
 * @param res Um ponteiro para a string de resultado onde o status de saída
 *        será anexado.
 * @return 1 em caso de sucesso, 0 em caso de falha de alocação.
 */
int	expand_exit_status(char **res)
{
	char	*temp;

	temp = itoa_exit_status();
	if (!temp)
	{
		free(*res);
		*res = NULL;
		return (0);
	}
	*res = append_str(*res, temp);
	free(temp);
	if (!*res)
		return (0);
	return (1);
}

/**
 * @brief Converte o status de saída global para uma string.
 *
 * @return Uma string contendo o valor numérico de `g_exit_status`,
 *         ou NULL em caso de falha de alocação (assumindo
 *         `ft_itoa` retorna NULL).
 */
char	*itoa_exit_status(void)
{
	return (ft_itoa(g_exit_status));
}

/**
 * @brief Expande a variável especial `$$` para o ID do processo atual.
 *
 * Converte ID do processo atual para uma string e anexa à string de resultado.
 *
 * @param res Um ponteiro para a string de resultado onde o ID do processo
 *        será anexado.
 * @return 1 em caso de sucesso, 0 em caso de falha de alocação.
 */
int	expand_process_id(char **res)
{
	char	*temp;

	temp = itoa_process_id();
	if (!temp)
	{
		free(*res);
		*res = NULL;
		return (0);
	}
	*res = append_str(*res, temp);
	free(temp);
	if (!*res)
		return (0);
	return (1);
}

/**
 * @brief Converte o ID do processo atual para uma string.
 *
 * @return Uma string contendo o valor numérico do PID,
 *         ou NULL em caso de falha de alocação (assumindo `ft_itoa` e `getpid`
 *         são válidos).
 */
char	*itoa_process_id(void)
{
	int		fd;
	size_t	read_return;
	int		buffer_length;
	char	buffer[8];
	char	**buffer_splitted;

	
	fd = open("/proc/self/stat", O_RDONLY);
	if (!fd)
		return NULL;
	read_return = read(fd, buffer, 8);
	if (!read_return)
		return NULL;
	buffer_splitted = ft_split(buffer, ' ');
	buffer_length = ft_strlen(buffer_splitted[0]);
	buffer_splitted[0][buffer_length] = '\0';
	return (buffer_splitted[0]);
}

/**
 * @brief Expande uma variável de ambiente padrão.
 *
 * Extrai o nome da variável de ambiente da string de entrada
 * (começando em `i_cmd`), obtém seu valor usando `get_env_val`, e anexa esse
 * valor à string de resultado.
 *
 * @param str A string de entrada que contém a variável de ambiente
 *        (e.g., "$VAR").
 * @param res Um ponteiro para a string de resultado onde o valor da variável
 *        será anexado.
 * @param i_cmd O índice na string `str` onde o nome da variável de ambiente
 *        começa (após o '$').
 * @return O número de caracteres do nome da variável processados.
 */
int	expand_env_var(const char *str, char **res, int i_cmd)
{
	char	var_input[256];
	int		i_var;
	char	*temp;
	int		start;

	start = i_cmd;
	i_var = 0;
	while (str[i_cmd] && (ft_isalnum(str[i_cmd]) || str[i_cmd] == '_'))
		var_input[i_var++] = str[i_cmd++];
	var_input[i_var] = '\0';
	temp = get_env_val(var_input);
	if (!temp)
	{
		free(*res);
		*res = NULL;
		return (0);
	}
	*res = append_str(*res, temp);
	free(temp);
	return (i_cmd - start);
}
