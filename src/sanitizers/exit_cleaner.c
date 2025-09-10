/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cleaner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo <gustavo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:19:33 by vboxuser          #+#    #+#             */
/*   Updated: 2025/09/09 22:53:18 by gustavo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	flush_pipe_str(t_pipe *pipes, t_command *cmd)
// {
// 	int	i;

// 	if (!pipes)
// 		return ;
// 	pipes->total_commands = count_commands(cmd);
// 	if (pipes)
// 	{
// 		if (pipes->pipe_fds)
// 		{
// 			i = 0;
// 			while (i < pipes->total_commands - 1)
// 			{
// 				if (pipes->pipe_fds[i])
// 					free(pipes->pipe_fds[i]);
// 				i++;
// 			}
// 			free(pipes->pipe_fds);
// 		}
// 		if (pipes->pids)
// 			free(pipes->pids);
// 	}
// }

void	flush_rsc_minishell(t_env *env, t_command *cmd, int exit_code)
{
	//flush_pipe_str(env->pipe, cmd);
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
