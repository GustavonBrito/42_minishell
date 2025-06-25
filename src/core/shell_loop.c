/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:50:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/24 17:41:48 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FILE HAS NORMINETTE ERRORS -> NOTES B4 FTS WITH ERRORS

void	shell_loop(void);
char	*obtain_current_directory(char **dir_ext,
			char *current_directory);

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
	char		*current_directory;
	char		**directory_splited;
	const char	*relative_path;

	signal(SIGINT, signal_handler); // Lida com CTRL + C
	signal(SIGQUIT, SIG_IGN); // Lida com CTRL + '\'
	while (1)
	{
		current_directory = getcwd(NULL, 0);
		if (!current_directory)
			return ;
		directory_splited = ft_split(current_directory, '/');
		relative_path = obtain_current_directory(directory_splited,
				current_directory);
		buffer_received = readline((const char *)relative_path);
		check_exit_condition(buffer_received); // Lida com CTRL + D
		if (*buffer_received)
		{
			add_history(buffer_received);
			g_exit_status = process_input(buffer_received);
		}
		free(buffer_received);
		free(current_directory);
	}
}

/**
 * @brief Obtém e formata o caminho relativo do diretório atual para o prompt.
 *
 * Constrói uma string para o prompt do shell que inclui o nome de usuário,
 * "@minishell:~/" e, se aplicável, o caminho relativo do diretório atual
 * a partir do diretório do usuário.
 *
 * @param dir_ext Um array de strings que representa o caminho do dir
 *                      atual dividido por '/'.
 * @param current_directory A string completa do caminho do diretório atual.
 * @return Uma string recém-alocada contendo o caminho formatado para o prompt.
 *         É responsabilidade do chamador liberar essa string.
 */

//norminette:too many vars and +25 lines needs to be chopped
char	*obtain_current_directory(char **dir_ext,
			char *current_directory)
{
	const char	*relative_path;
	char		*user_path;
	int			user_length;
	int			relative_path_length;
	int			flag;
	int			i;

	i = -1;
	flag = 0;
	while (dir_ext[++i])
	{
		if (ft_strncmp(dir_ext[i], getenv("USER"),
				ft_strlen(getenv("USER"))) == 0 && dir_ext[i + 1] != NULL)
		{
			i++;
			flag = 1;
			break ;
		}
	}
	if (flag == 1)
	{
		relative_path = ft_strnstr(current_directory, dir_ext[i],
				ft_strlen(current_directory));
		relative_path_length = ft_strlen(relative_path);
	}
	else
	{
		relative_path = NULL;
		relative_path_length = 0;
	}
	user_length = ft_strlen(getenv("USER"));
	relative_path_length = user_length + relative_path_length;
	user_path = malloc(sizeof(char) * (relative_path_length + user_length
				+ 14));
	ft_strlcpy(user_path, (const char *)getenv("USER"), user_length + 1);
	ft_strlcat(user_path, "@minishell:~/", user_length + 14);
	user_length = ft_strlen(user_path);
	if (relative_path != NULL)
	{
		ft_strlcat(user_path, relative_path, user_length + relative_path_length
			+ 1);
		user_length = ft_strlen(user_path);
	}
	ft_strlcat(user_path, " ", user_length + 2);
	return (user_path);
}
