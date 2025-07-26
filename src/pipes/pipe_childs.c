/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_childs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:51:04 by luiza             #+#    #+#             */
/*   Updated: 2025/07/25 22:06:15 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		setup_child_pipes(t_pipe *pipes, int cmd_index);
void		execute_child_command(t_command *cmd);
static int	handle_builtin_in_pipe(t_command *cmd);
static void	close_unused_pipes(t_pipe *pipes, int cmd_index);

/**
 * @brief Configura pipes no processo filho
 *
 * @param pipes Estrutura de controle de pipes
 */
void setup_child_pipes(t_pipe *pipes, int cmd_index)
{
	if (cmd_index > 0)
	{
		if (pipes->pipe_fds[cmd_index-1][0] != -1)
		{
			if (dup2(pipes->pipe_fds[cmd_index-1][0], STDIN_FILENO) == -1)
			{
				perror("DEBUG PIPES: dup2 input failed");
				exit(1);
			}
		}
	}
	if (cmd_index < pipes->total_commands - 1)
	{
		if (pipes->pipe_fds[cmd_index][1] != -1)
		{
			if (dup2(pipes->pipe_fds[cmd_index][1], STDOUT_FILENO) == -1)
			{
				perror("DEBUG PIPES: dup2 output failed");
				exit(1);
			}
		}
	}
	close_unused_pipes(pipes, cmd_index);
}

/**
 * @brief Executa comando no processo filho
 *
 * @param cmd Comando a ser executado
 */
void	execute_child_command(t_command *cmd)
{
	int	exit_code;
	
	if (!cmd || !cmd->args || !cmd->args[0])
		exit(127);
	if (check_builtin(cmd))
	{
		exit_code = handle_builtin_in_pipe(cmd);
		exit(exit_code);
	}
	exit_code = execute_with_execve(cmd);
	exit(exit_code);
}

static int	handle_builtin_in_pipe(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		g_exit_status = 1;
		return (127);
	}
	is_builtin(cmd);
	return (g_exit_status);
}

static void	close_unused_pipes(t_pipe *pipes, int cmd_index)
{
	int	i;

	i = 0;
	while (i < (pipes->total_commands - 1))
	{
		if (i != (cmd_index - 1) && i != cmd_index)
		{
			if (pipes->pipe_fds[i][0] != -1)
			{
				close(pipes->pipe_fds[i][0]);
				pipes->pipe_fds[i][0] = -1;
			}
			if (pipes->pipe_fds[i][1] != -1)
			{
				close(pipes->pipe_fds[i][1]);
				pipes->pipe_fds[i][1] = -1;
			}
		}
		i++;
	}
}
