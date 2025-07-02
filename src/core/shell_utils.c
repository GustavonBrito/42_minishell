/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 23:07:58 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/27 03:18:33 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_exit_condition(char *buffer_received);
void	signal_handler(int signal);
char	*obtain_current_directory(void);
char	*get_env_or_cleanup(const char *var, char *to_free);

/**
 * @brief Verifica a condição de saída do shell.
 *
 * Esta função verifica se o buffer de entrada recebido é NULL, o que geralmente
 * indica que o usuário pressionou Ctrl+D (EOF). Se for NULL, imprime "exit"
 * e encerra o programa.
 *
 * @param buffer_received A string lida pelo readline.
 */
void	check_exit_condition(char *buffer_received)
{
	if (buffer_received == NULL)
	{
		ft_printf("exit\n");
		exit(0);
	}
}

/**
 * @brief Manipulador de sinais para interrupção do shell.
 *
 * Lida com o sinal `SIGINT` (Ctrl+C). Quando o sinal é recebido,
 * ele imprime uma nova linha, limpa a linha atual do readline,
 * redesenha o prompt e define o status de saída global para 130.
 * O parâmetro `signal` é `(void)` pois não é usado diretamente na função.
 *
 * @param signal O número do sinal recebido.
 */
void	signal_handler(int signal)
{
	(void)signal;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}

/**
 * @brief Obtém o diretório de trabalho atual.
 *
 * Usa getcwd() para obter o caminho absoluto do diretório corrente.
 *
 * @return String alocada com o diretório atual, que deve ser liberada pelo chamador.
 *         Retorna NULL em caso de erro.
 */

char	*obtain_current_directory(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
		return (NULL);
	return (dir);
}

/**
 * @brief Obtém o valor de uma variável de ambiente ou libera memória auxiliar.
 *
 * Tenta obter o valor da variável de ambiente `var` usando getenv().
 * Se não for encontrada, libera a string `to_free` e retorna NULL.
 *
 * @param var Nome da variável de ambiente a ser buscada.
 * @param to_free String a ser liberada caso a variável não seja encontrada.
 * @return Valor da variável se encontrado, ou NULL se não.
 */

char	*get_env_or_cleanup(const char *var, char *to_free)
{
	char	*value;

	value = getenv(var);
	if (!value)
	{
		free(to_free);
		return (NULL);
	}
	return (value);
}
