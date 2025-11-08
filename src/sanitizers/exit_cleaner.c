/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cleaner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:19:33 by vboxuser          #+#    #+#             */
/*   Updated: 2025/09/18 19:38:56 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	flush_rsc_minishell(t_env *env, t_command *cmd, int exit_code)
{
	if (env->pipe != NULL)
		cleanup_pipeline(env->pipe);
	free_tokens(env->tokens);
	free_env_list(env);
	free(*handle_pipe_mode());
	free(*handle_heredoc_redir());
	free(*handle_exit_status());
	rl_clear_history();
	free_commands(cmd);
	exit(exit_code);
}

void	close_dup_fds(int fd1, int fd2)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
}

void	init_exit_struct(void)
{
	t_exit_status	*exit_status;

	exit_status = NULL;
	exit_status = ft_calloc(1, sizeof(t_exit_status));
	*handle_exit_status() = exit_status;
}

t_exit_status	**handle_exit_status(void)
{
	static t_exit_status	*exit_status;

	return (&exit_status);
}
