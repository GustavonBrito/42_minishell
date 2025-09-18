/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:33:30 by gustavo           #+#    #+#             */
/*   Updated: 2025/09/18 19:22:22 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_command(t_command *cmd);
int		execute_builtin(t_command *cmd);
int		execute_external_command(t_command *cmd);
void	handle_command_execution(t_command *cmd);
int		check_builtin(t_command *cmd);

int	execute_command(t_command *cmd)
{
	int	saved_stdin;
	int	saved_stdout;
	int	redir_result;
	int	exec_result;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ((*handle_exit_status())->exit_status = 1, 0);
	saved_stdin = dup(STDIN_FILENO);
	(*handle_t_env(NULL))->fd_stdin = saved_stdin;
	saved_stdout = dup(STDOUT_FILENO);
	(*handle_t_env(NULL))->fd_stdout = saved_stdout;
	redir_result = setup_redirections(cmd);
	if (redir_result != 0)
		return (restore_std_fds(saved_stdin, saved_stdout), redir_result);
	if (check_builtin(cmd))
		exec_result = execute_builtin(cmd);
	else
	{
		if (ft_strncmp(cmd->args[0], "cat", 3) == 0 && cmd->args[1] == NULL)
			(*handle_t_env(NULL))->cat_flag = 1;
		exec_result = execute_external_command(cmd);
	}
	restore_std_fds(saved_stdin, saved_stdout);
	return (exec_result);
}

int	execute_builtin(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		(*handle_exit_status())->exit_status = 1;
		return ((*handle_exit_status())->exit_status);
	}
	is_builtin(cmd);
	return ((*handle_exit_status())->exit_status);
}

int	execute_external_command(t_command *cmd)
{
	pid_t	pid;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		(*handle_exit_status())->exit_status = 1;
		return ((*handle_exit_status())->exit_status);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork ");
		(*handle_exit_status())->exit_status = 1;
		return ((*handle_exit_status())->exit_status);
	}
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		exit(run_external(cmd, cmd));
	}
	else
	{
		(*handle_exit_status())->exit_status = handle_parent_process(pid);
		return ((*handle_exit_status())->exit_status);
	}
}

void	handle_command_execution(t_command *cmd)
{
	t_command	*current;
	int			result;

	if (!cmd)
	{
		(*handle_exit_status())->exit_status = 1;
		return ;
	}
	current = cmd;
	if (has_pipes(current))
	{
		result = execute_pipeline(current);
		(*handle_exit_status())->exit_status = result;
	}
	else
	{
		result = execute_command(current);
		(*handle_exit_status())->exit_status = result;
	}
}

int	check_builtin(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		(*handle_exit_status())->exit_status = 1;
		return (0);
	}
	if ((ft_strncmp(cmd->args[0], "echo", 4) == 0
			&& ft_strlen(cmd->args[0]) == 4) || (ft_strncmp(cmd->args[0], "cd",
				2) == 0 && ft_strlen(cmd->args[0]) == 2)
		|| (ft_strncmp(cmd->args[0], "pwd", 3) == 0
			&& ft_strlen(cmd->args[0]) == 3) || (ft_strncmp(cmd->args[0],
				"export", 6) == 0 && ft_strlen(cmd->args[0]) == 6)
		|| (ft_strncmp(cmd->args[0], "unset", 5) == 0
			&& ft_strlen(cmd->args[0]) == 5) || (ft_strncmp(cmd->args[0], "env",
				3) == 0 && ft_strlen(cmd->args[0]) == 3)
		|| (ft_strncmp(cmd->args[0], "exit", 4) == 0
			&& ft_strlen(cmd->args[0]) == 4))
		return (1);
	else
		return (0);
}
