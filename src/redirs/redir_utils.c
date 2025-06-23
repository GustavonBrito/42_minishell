/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 00:35:22 by luiza             #+#    #+#             */
/*   Updated: 2025/06/22 21:23:04 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		create_heredoc_file(char *delimiter);
void	restore_std_fds(int saved_stdin, int saved_stdout);

/**
 * @brief Cria um "arquivo" (pipe) para o conteúdo de um heredoc.
 *
 * Esta função solicita entrada do usuário linha por linha, escrevendo-a em um pipe,
 * até que a linha digitada corresponda ao delimitador. A extremidade de escrita
 * do pipe é fechada, e a extremidade de leitura é retornada para ser usada como STDIN.
 *
 * @param delimiter A string que atua como delimitador para o fim da entrada do heredoc.
 * @return O descritor de arquivo da extremidade de leitura do pipe, ou -1 em caso de erro.
 */
int	create_heredoc_file(char *delimiter)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	ft_printf("> ");
	line = readline("");
	while (line != NULL)
	{
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& ft_strlen(line) == ft_strlen(delimiter))
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
		ft_printf("> ");
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}


/**
 * @brief Restaura os descritores de arquivo padrão (stdin, stdout).
 *
 * Esta função é usada para reverter os redirecionamentos de E/S feitos
 * durante a execução de um comando. Ela restaura os descritores de arquivo
 * para seus valores originais salvos, se eles forem válidos (não -1).
 *
 * @param saved_stdin O descritor de arquivo original para STDIN.
 * @param saved_stdout O descritor de arquivo original para STDOUT.
 */
void	restore_std_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}
