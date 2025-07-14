/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_childs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:51:04 by luiza             #+#    #+#             */
/*   Updated: 2025/07/05 16:11:26 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		setup_child_pipes(t_pipe *pipes);
void		execute_child_command(t_command *cmd);

/**
 * @brief Configura pipes no processo filho
 *
 * @param pipes Estrutura de controle de pipes
 */
void	setup_child_pipes(t_pipe *pipes)
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
}

/**
 * @brief Executa comando no processo filho
 *
 * @param cmd Comando a ser executado
 */
void	execute_child_command(t_command *cmd)
{
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
