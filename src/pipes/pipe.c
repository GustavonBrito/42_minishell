/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:51:04 by luiza             #+#    #+#             */
/*   Updated: 2025/06/23 15:39:40 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			has_pipes(t_command *cmd);
int			execute_pipeline(t_command *cmd);
static int	exec_pip_cmd(t_command *cmd, int **pipes, int cmd_i, int cmd_count);
static void	setup_pipe_fds(int **pipes, int cmd_index, int cmd_count);

int	has_pipes(t_command *cmd)
{
	if (!cmd)
		return (0);
	return (cmd->next != NULL);
}

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
		if (check_builtin(cmd->args[0]))
		{
			is_builtin(cmd->args);
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
