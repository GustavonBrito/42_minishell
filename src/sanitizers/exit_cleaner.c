/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cleaner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo <gustavo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:19:33 by vboxuser          #+#    #+#             */
/*   Updated: 2025/09/15 20:50:10 by gustavo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	flush_rsc_minishell(t_env *env, t_command *cmd, int exit_code)
{
	if (env->pipe != NULL)
		cleanup_pipeline(env->pipe);
	free_tokens(env->tokens);
	free_env_list(env);
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
