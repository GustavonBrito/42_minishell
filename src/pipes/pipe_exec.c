/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:51:04 by luiza             #+#    #+#             */
/*   Updated: 2025/07/05 16:28:20 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				has_pipes(t_command *cmd);
int				execute_pipeline(t_command *cmd);
static pid_t	pipe_loop(t_command *cmd, t_pipe *pipes);
static int		exec_pip_cmd(t_command *cmd, t_pipe *pipes);
static int		wait_last_process(pid_t last_pid, t_pipe *pipes);

/**
 * @brief Verifica se há mais de um comando encadeado.
 *
 * Retorna 1 se o comando atual possui um próximo comando na lista,
 * indicando a existência de pipes. Caso contrário, retorna 0.
 *
 * @param cmd Ponteiro para a estrutura `t_command`.
 * @return 1 se houver pipe, 0 caso contrário.
 */

int	has_pipes(t_command *cmd)
{
	if (!cmd)
		return (0);
	return (cmd->next != NULL);
}

/**
 * @brief Executa o pipeline de comandos
 *
 * @param cmd Ponteiro para a lista de comandos encadeados.
 * @return Código de status do último comando executado.
 */
int	execute_pipeline(t_command *cmd)
{
	pid_t		last_pid;
	t_pipe		pipes;

	if (!cmd)
		return (0);
	if (!cmd->next)
		return (execute_command(cmd));
	init_pipeline(&pipes, cmd);
	last_pid = pipe_loop(cmd, &pipes);
	if (last_pid == -1)
		return (1);
	return (wait_last_process(last_pid, &pipes));
}

/**
 * @brief Executa loop principal do pipeline
 *
 * @param cmd Comando inicial
 * @param pipes Estrutura de controle de pipes
 * @return PID do último processo ou -1 em erro
 */
static pid_t	pipe_loop(t_command *cmd, t_pipe *pipes)
{
	pid_t		last_pid;
	pid_t		pid;
	t_command	*current;

	last_pid = -1;
	current = cmd;
	while (current)
	{
		if (current->next && create_pipe(pipes))
			return (-1);
		pid = exec_pip_cmd(current, pipes);
		if (pid == -1)
		{
			close_child(pipes);
			return (1);
		}
		if (!current->next)
			last_pid = pid;
		update_pipes(pipes, current);
		current = current->next;
	}
	return (last_pid);
}

/**
 * @brief Executa um comando dentro de uma pipeline.
 *
 * @param cmd Ponteiro para o comando a ser executado.
 * @param pipes Estrutura de controle de pipes e índices.
 * @return PID do processo filho ou -1 em erro.
 */
static int	exec_pip_cmd(t_command *cmd, t_pipe *pipes)
{
	pid_t	pid;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: error with fork");
		return (-1);
	}
	else if (pid == 0)
	{
		setup_child_pipes(pipes);
		if (setup_redirections(cmd) != 0)
			exit(1);
		execute_child_command(cmd);
	}
	return (pid);
}

/**
 * @brief Aguarda o término do último processo e define status
 *
 * @param last_pid PID do último processo
 * @param pipes Estrutura de controle de pipes
 * @return Status de saída
 */
static int	wait_last_process(pid_t last_pid, t_pipe *pipes)
{
	int	status;

	if (pipes->prev_pipe_read != -1)
		close(pipes->prev_pipe_read);
	if (last_pid != -1)
	{
		waitpid(last_pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
	}
	return (g_exit_status);
}
