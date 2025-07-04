/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:51:04 by luiza             #+#    #+#             */
/*   Updated: 2025/07/04 20:26:50 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FILE HAS NORMINETTE ERRORS -> NOTES B4 FTS WITH ERRORS

int			has_pipes(t_command *cmd);
int			execute_pipeline(t_command *cmd);
static int	exec_pip_cmd(t_command *cmd, t_pipe *pipes);

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
 * Itera sobre a lista de comandos, criando os pipes necessários
 * e processos filhos via fork. Configura redirecionamentos,
 * executa built-ins ou comandos externos, e aguarda o término
 * do último processo.
 *
 * @param cmd Ponteiro para a lista de comandos encadeados.
 * @return Código de status do último comando executado.
 */

//norminette: many vars and +25 lines: needs to be chopped
int	execute_pipeline(t_command *cmd)
{
	pid_t		pid;
	pid_t		last_pid;
	int			status;
	t_command	*current;
	t_pipe		pipes;

	if (!cmd)
		return (0);
	if (!cmd->next)
		return (execute_command(cmd));
	pipes.prev_pipe_read = -1;
	pipes.cmd_index = 0;
	pipes.total_commands = count_commands(cmd);
	last_pid = -1;
	current = cmd;
	while (current)
	{
		if (current->next)
		{
			if (pipe(pipes.curr_pipe) == -1)
			{
				perror("minishell: pipeline creation failed");
				if (pipes.prev_pipe_read != -1)
					close(pipes.prev_pipe_read);
				return (1);
			}
		}
		pid = exec_pip_cmd(current, &pipes);
		if (pid == -1)
		{
			close_child(&pipes);
			return (1);
		}
		if (!current->next)
			last_pid = pid;
		if (pipes.prev_pipe_read != -1)
			close(pipes.prev_pipe_read);
		if (current->next)
		{
			close(pipes.curr_pipe[1]);
			pipes.prev_pipe_read = pipes.curr_pipe[0];
		}
		current = current->next;
		pipes.cmd_index++;
	}
	if (pipes.prev_pipe_read != -1)
		close(pipes.prev_pipe_read);
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

/**
 * @brief Executa um comando dentro de uma pipeline.
 *
 * Cria um processo filho via `fork()`. No filho:
 * - Configura os descritores de arquivo para os pipes.
 * - Executa redirecionamentos.
 * - Executa o comando (built-in ou externo via `execvp()`).
 *
 * @param cmd Ponteiro para o comando a ser executado.
 * @param pipes Estrutura de controle de pipes e índices.
 * @return PID do processo filho ou 1 em erro.
 */

//norminette:+25 lines needs to be chopped
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
		if (pipes->prev_pipe_read != -1)
		{
			dup2(pipes->prev_pipe_read, STDIN_FILENO);
			close(pipes->prev_pipe_read);
		}
		if (pipes->cmd_index < pipes->total_commands - 1)
		{
			dup2(pipes->curr_pipe[1], STDOUT_FILENO);
			close(pipes->curr_pipe[1]);
			close(pipes->curr_pipe[0]);
		}
		if (setup_redirections(cmd) != 0)
			exit(1);
		if (check_builtin(cmd))
		{
			is_builtin(cmd);
			exit(g_exit_status);
		}
		else
		{
			if (execvp(cmd->args[0], cmd->args) == -1)
			{
				ft_printf("minishell: %s: command not found\n", cmd->args[0]);
				exit(127);
			}
		}
	}
	return (pid);
}
