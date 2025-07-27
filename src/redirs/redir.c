/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 23:14:39 by luiza             #+#    #+#             */
/*   Updated: 2025/07/26 03:22:07 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_redirections(t_command *cmd);
int	handle_input_redirection(t_redir *redir);
int	handle_output_redirection(t_redir *redir);
int	handle_append_redirection(t_redir *redir);
int	handle_heredoc(t_redir *redir);

/**
 * @brief Configura os redirecionamentos para um comando.
 *
 * Esta função percorre a lista de redirecionamentos de um
 * comando (`cmd->redirs`)
 * e chama a função de tratamento específica para cada tipo de redirecionamento
 * (entrada, saída, append, heredoc). Se algum redirecionamento falhar, retorna
 * imediatamente o código de erro.
 *
 * @param cmd Um ponteiro para a estrutura `t_command` contendo os redirs.
 * @return 0 em caso de sucesso (todos os redirecionamentos configurados),
 *         ou um código de erro (geralmente 1) se algum redirecionamento falhar
 */
int	setup_redirections(t_command *cmd)
{
	t_redir	*current_redir;
	int		result;
	int		error_occurred;

	if (!cmd || !cmd->redirs)
		return (0);
	current_redir = cmd->redirs;
	error_occurred = 0;
	while (current_redir)
	{
		if (current_redir->type == REDIR_IN)
			result = handle_input_redirection(current_redir);
		else if (current_redir->type == REDIR_OUT)
			result = handle_output_redirection(current_redir);
		else if (current_redir->type == REDIR_APPEND)
			result = handle_append_redirection(current_redir);
		else if (current_redir->type == HEREDOC)
			result = handle_heredoc(current_redir);
		else
			result = 0;
		if (result != 0)
			error_occurred = result;
		current_redir = current_redir->next;
	}
	return (error_occurred);
}

/**
 * @brief Lida com redirecionamento de entrada (`<`).
 *
 * Abre o arquivo especificado em modo somente leitura e redireciona a entrada
 * padrão (STDIN) para ele usando `dup2`. Reporta erros de abertura de arquivo
 * ou de `dup2`.
 *
 * @param redir ponteiro para a estrutura `t_redir` contendo o nome do arquivo
 *              para redirecionamento de entrada.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int	handle_input_redirection(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("minishell: %s: ", redir->file);
		perror("");
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

/**
 * @brief Lida com redirecionamento de saída (`>`).
 *
 * Abre (ou cria) o arquivo especificado em modo de escrita, truncando-o se já
 * existir, e redireciona a saída padrão (STDOUT) para ele usando `dup2`.
 * Reporta erros.
 *
 * @param redir ponteiro para a estrutura `t_redir` contendo o nome do arquivo
 *              para redirecionamento de saída.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int	handle_output_redirection(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_printf("minishell: %s: ", redir->file);
		perror("");
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

/**
 * @brief Lida com redirecionamento de saída em modo de append (`>>`).
 *
 * Abre (ou cria) o arquivo especificado em modo de escrita, anexando ao final
 * se já existir, e redireciona a saída padrão (STDOUT) para ele usando `dup2`.
 * Reporta erros.
 *
 * @param redir Um ponteiro para a estrutura `t_redir` contendo o nome do
 *        arquivo para redirecionamento de append.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int	handle_append_redirection(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_printf("minishell: %s: ", redir->file);
		perror("");
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

/**
 * @brief Lida com redirecionamento de heredoc (`<<`).
 *
 * Cria um arquivo temporário (ou pipe) para o conteúdo do heredoc, solicita a
 * entrada do usuário até encontrar o delimitador, e então redireciona entrada
 * padrão (STDIN) para esse arquivo/pipe.
 *
 * @param redir Um ponteiro para a estrutura `t_redir` contendo o delimitador
 *              para o heredoc.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int	handle_heredoc(t_redir *redir)
{
	int		heredoc_fd;
	char	*delimiter;

	delimiter = redir->file;
	heredoc_fd = create_heredoc_file(delimiter);
	if (heredoc_fd == -1)
		return (1);
	if (dup2(heredoc_fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(heredoc_fd);
		return (1);
	}
	close(heredoc_fd);
	return (0);
}
