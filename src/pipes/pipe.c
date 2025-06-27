/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:51:04 by luiza             #+#    #+#             */
/*   Updated: 2025/06/26 22:53:09 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FILE HAS NORMINETTE ERRORS -> NOTES B4 FTS WITH ERRORS

int			has_pipes(t_command *cmd);
int			execute_pipeline(t_command *cmd);
static int	exec_pip_cmd(t_command *cmd, int **pipes, int cmd_i, int cmd_count);
static void	setup_pipe_fds(int **pipes, int cmd_index, int cmd_count);

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
 * @brief Executa uma sequência de comandos conectados por pipes.
 *
 * Cria os pipes necessários, executa cada comando em um processo separado,
 * conecta suas saídas e entradas, e espera o término de todos os processos.
 * Atualiza a variável global `g_exit_status` com o status do último comando.
 *
 * @param cmd Ponteiro para a lista de comandos encadeados.
 * @return Código de status do último comando executado.
 */

//norminette: many vars and +25 lines: needs to be chopped
int	execute_pipeline(t_command *cmd)
{
	int			cmd_count;
	int			**pipes;
	pid_t		*pids;
	int			i;
	int			status;
	t_command	*current;

	if (!cmd)
		return (0);
	cmd_count = count_commands(cmd);
	if (cmd_count == 1)
		return (execute_command(cmd));
	pipes = create_pipes(cmd_count);
	if (!pipes && cmd_count > 1)
	{
		perror("minishell: pipeline creation failed");
		return (1);
	}
	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
	{
		free_pipes(pipes, cmd_count - 1);
		return (1);
	}
	current = cmd;
	i = 0;
	while (current && i < cmd_count)
	{
		pids[i] = exec_pip_cmd(current, pipes, i, cmd_count);
		if (pids[i] == 1)
		{
			free(pids);
			close_all_pipes(pipes, cmd_count - 1);
			free_pipes(pipes, cmd_count - 1);
			return (1);
		}
		current = current->next;
		i++;
	}
	close_all_pipes(pipes, cmd_count - 1);
	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	free(pids);
	free_pipes(pipes, cmd_count - 1);
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
 * @param pipes Array de pipes abertos.
 * @param cmd_i Índice do comando atual.
 * @param cmd_count Quantidade total de comandos na pipeline.
 * @return PID do processo filho ou 1 em erro.
 */

//norminette:+25 lines needs to be chopped
static int	exec_pip_cmd(t_command *cmd, int **pipes, int cmd_i, int cmd_count)
{
	pid_t	pid;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: error with fork");
		return (1);
	}
	else if (pid == 0)
	{
		setup_pipe_fds(pipes, cmd_i, cmd_count);
		close_all_pipes(pipes, cmd_count - 1);
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

/**
 * @brief Configura os descritores de arquivo padrão para um comando da pipeline.
 *
 * Redireciona a entrada e/ou saída padrão do processo conforme sua posição
 * na pipeline:
 * - Entrada recebe o lado de leitura do pipe anterior, se houver.
 * - Saída recebe o lado de escrita do próximo pipe, se houver.
 *
 * @param pipes Array de pipes abertos.
 * @param cmd_index Índice do comando atual.
 * @param cmd_count Quantidade total de comandos na pipeline.
 */

static void	setup_pipe_fds(int **pipes, int cmd_index, int cmd_count)
{
	if (cmd_index > 0)
	{
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	}
	if (cmd_index < cmd_count - 1)
	{
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
	}
}
