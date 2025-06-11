/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 00:38:15 by luiza             #+#    #+#             */
/*   Updated: 2025/06/11 00:40:34 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_command(t_command *cmd);
int		execute_builtin_with_redirections(t_command *cmd);
int		execute_external_command(t_command *cmd);
void	handle_command_execution(t_command *cmd);

int	execute_command(t_command *cmd)
{
	int	saved_stdin;
	int	saved_stdout;
	int	redir_result;
	int	exec_result;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	redir_result = setup_redirections(cmd);
	if (redir_result != 0)
	{
		restore_std_fds(saved_stdin, saved_stdout);
		return (redir_result);
	}
	if (is_builtin_command(cmd->args[0]))
		exec_result = execute_builtin_with_redirections(cmd);
	else
		exec_result = execute_external_command(cmd);
	restore_std_fds(saved_stdin, saved_stdout);
	return (exec_result);
}

int	execute_builtin_with_redirections(t_command *cmd)
{
	char	*command_line;
	int		i;
	int		total_len;

	total_len = 0;
	i = 0;
	while (cmd->args[i])
	{
		total_len += ft_strlen(cmd->args[i]) + 1;
		i++;
	}
	command_line = malloc(total_len + 1);
	if (!command_line)
		return (1);
	command_line[0] = '\0';
	i = 0;
	while (cmd->args[i])
	{
		ft_strlcat(command_line, cmd->args[i], total_len + 1);
		if (cmd->args[i + 1])
			ft_strlcat(command_line, " ", total_len + 1);
		i++;
	}
	is_builtin(command_line);
	free(command_line);
	return (0);
}

int	execute_external_command(t_command *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	else if (pid == 0)
	{
		if (execvp(cmd->args[0], cmd->args) == -1)
		{
			ft_printf("minishell: %s: command not found\n", cmd->args[0]);
			exit(127);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}
	return (0);
}

void	handle_command_execution(t_command *cmd)
{
	t_command	*current;

	current = cmd;
	while (current)
	{
		g_exit_status = execute_command(current);
		current = current->next;
		// TODO: implement pipes
	}
}

int	is_builtin_command(char *cmd)
{
	if (!cmd)
		return (0);

	if (ft_strncmp(cmd, "echo", 4) == 0 && (cmd[4] == '\0'))
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0 && (cmd[2] == '\0'))
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0 && (cmd[3] == '\0'))
		return (1);
	else if (ft_strncmp(cmd, "export", 6) == 0 && (cmd[6] == '\0'))
		return (1);
	else if (ft_strncmp(cmd, "unset", 5) == 0 && (cmd[5] == '\0'))
		return (1);
	else if (ft_strncmp(cmd, "env", 3) == 0 && (cmd[3] == '\0'))
		return (1);
	else if (ft_strncmp(cmd, "exit", 4) == 0 && (cmd[4] == '\0'))
		return (1);

	return (0);
}
