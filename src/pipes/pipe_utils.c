/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:55:08 by luiza             #+#    #+#             */
/*   Updated: 2025/07/05 16:29:06 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipeline(t_pipe *pipes, t_command *cmd);
int		count_commands(t_command *cmd);
int		create_pipe(t_pipe *pipes);
void	update_pipes(t_pipe *pipes, t_command *current);
void	close_child(t_pipe *pipes);

/**
 * @brief Inicializa a estrutura de pipes para o pipeline
 *
 * @param pipes Estrutura de controle de pipes
 * @param cmd Lista de comandos para contar o total
 */
void	init_pipeline(t_pipe *pipes, t_command *cmd)
{
	pipes->prev_pipe_read = -1;
	pipes->cmd_index = 0;
	pipes->total_commands = count_commands(cmd);
}

/**
 * @brief Conta o número de comandos em uma lista encadeada de `t_command`.
 *
 * Percorre a lista de comandos e retorna a quantidade de elementos.
 *
 * @param cmd Ponteiro para o primeiro comando.
 * @return Número de comandos na lista.
 */

int	count_commands(t_command *cmd)
{
	int			count;
	t_command	*current;

	if (!cmd)
		return (0);
	count = 0;
	current = cmd;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/**
 * @brief Cria pipe e trata erros
 *
 * @param pipes Estrutura de controle de pipes
 * @return 0 em sucesso, 1 em erro
 */
int	create_pipe(t_pipe *pipes)
{
	if (pipe(pipes->curr_pipe) == -1)
	{
		perror("minishell: pipeline creation failed");
		if (pipes->prev_pipe_read != -1)
			close(pipes->prev_pipe_read);
		return (1);
	}
	return (0);
}

/**
 * @brief Atualiza pipes após execução de comando
 *
 * @param pipes Estrutura de controle de pipes
 * @param current Comando atual
 */
void	update_pipes(t_pipe *pipes, t_command *current)
{
	if (pipes->prev_pipe_read != -1)
		close(pipes->prev_pipe_read);
	if (current->next)
	{
		close(pipes->curr_pipe[1]);
		pipes->prev_pipe_read = pipes->curr_pipe[0];
	}
	pipes->cmd_index++;
}

/**
 * @brief Fecha o descritor de leitura do pipe anterior no filho.
 *
 * Utilizada no processo filho para fechar o FD de leitura herdado
 * antes de configurar os redirecionamentos e executar o comando.
 *
 * @param pipes APonteiro para a estrutura de controle de pipes.
 */

void	close_child(t_pipe *pipes)
{
	if (pipes->prev_pipe_read != 1)
		close(pipes->prev_pipe_read);
}
