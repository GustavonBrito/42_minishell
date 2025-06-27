/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:50:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/27 03:03:22 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		shell_loop(void);
static char	*create_prompt(void);
static char	*format_path(char *current_dir, char *home_dir);
static char	*build_prompt(char *username, char *display_path);

/**
 * @brief O loop principal do shell.
 *
 * Esta função implementa o loop interativo do minishell. Ela continuamente:
 * 1. Obtém o diretório de trabalho atual para exibir no prompt.
 * 2. Define os manipuladores de sinal (Ctrl+C e Ctrl+\).
 * 3. Lê a entrada do usuário usando `readline`.
 * 4. Verifica a condição de saída (Ctrl+D).
 * 5. Adiciona a entrada ao histórico do readline.
 * 6. Processa a entrada (lex, parse, expand, execute).
 * 7. Libera a memória alocada para o buffer de entrada e o diretório atual.
 *
 * Permanece em execução até o programa ser encerrado.
 */
void	shell_loop(void)
{
	char		*buffer_received;
	char		*prompt;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		prompt = create_prompt();
		if (!prompt)
			return ;
		buffer_received = readline(prompt);
		free(prompt);
		check_exit_condition(buffer_received);
		if (*buffer_received)
		{
			add_history(buffer_received);
			g_exit_status = process_input(buffer_received);
		}
		free(buffer_received);
	}
}

/**
 * @brief Cria o prompt do minishell para exibir no readline.
 *
 * Monta o prompt customizado no formato:
 * "usuario@minishell:<diretorio_atual>$ "
 *
 * Obtém o diretório atual com getcwd() e o nome de usuário via getenv("USER").
 * Se o diretório estiver dentro do $HOME, substitui essa parte por '~'.
 *
 * @return String alocada com o prompt, que deve ser liberada pelo chamador.
 *         Retorna NULL em caso de erro.
 */

static char	*create_prompt(void)
{
	char	*current_dir;
	char	*username;
	char	*home_dir;
	char	*display_path;
	char	*prompt;

	current_dir = obtain_current_directory();
	if (!current_dir)
		return (NULL);
	username = get_env_or_cleanup("USER", current_dir);
	if (!username)
		return (NULL);
	home_dir = getenv("HOME");
	display_path = format_path(current_dir, home_dir);
	if (!display_path)
	{
		free(current_dir);
		return (NULL);
	}
	prompt = build_prompt(username, display_path);
	free(current_dir);
	if (display_path != current_dir)
		free(display_path);
	return (prompt);
}

/**
 * @brief Formata o caminho do diretório atual para exibição no prompt.
 *
 * Se o diretório atual estiver dentro do diretório HOME, substitui a parte do
 * caminho equivalente ao HOME por '~'. Caso contrário, retorna o caminho atual.
 *
 * @param current_dir Caminho absoluto atual obtido por getcwd().
 * @param home_dir Diretório HOME do usuário obtido por getenv("HOME").
 * @return String alocada com o caminho formatado ou o próprio current_dir.
 *         Se retornar uma nova string, ela deve ser liberada pelo chamador.
 *         Se retornar current_dir, o chamador não deve liberar.
 */

static char	*format_path(char *current_dir, char *home_dir)
{
	char	*relative_path;
	char	*display_path;
	int		home_len;

	if (!home_dir)
		return (current_dir);
	home_len = ft_strlen(home_dir);
	if (ft_strncmp(current_dir, home_dir, home_len) != 0)
		return (current_dir);
	if (current_dir[home_len] == '\0')
		return (ft_strdup("~"));
	if (current_dir[home_len] == '/')
	{
		relative_path = current_dir + home_len + 1;
		display_path = ft_strjoin("~/", relative_path);
		return (display_path);
	}
	return (current_dir);
}

/**
 * @brief Monta a string final do prompt do minishell.
 *
 * Concatena o nome de usuário, o prefixo "@minishell:", o caminho atual ou '~'
 * e o caractere "$ " para formar o prompt exibido no readline.
 *
 * @param username Nome de usuário obtido de getenv("USER").
 * @param display_path Caminho formatado do diretório atual.
 * @return String alocada com o prompt completo. Deve ser liberada pelo chamador.
 */

static char	*build_prompt(char *username, char *display_path)
{
	char	*return_path;
	char	*full_prompt;

	return_path = ft_strjoin(username, "@minishell:");
	if (!return_path)
		return (NULL);
	full_prompt = ft_strjoin(return_path, display_path);
	free(return_path);
	if (!full_prompt)
		return (NULL);
	return_path = ft_strjoin(full_prompt, "$ ");
	free(full_prompt);
	return (return_path);
}
