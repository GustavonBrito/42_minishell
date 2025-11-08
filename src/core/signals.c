/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:26:54 by lukorman          #+#    #+#             */
/*   Updated: 2025/09/18 19:22:22 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signal);
void	setup_heredoc_signals(void);
void	restore_normal_signals(void);

void	signal_handler(int signal_received)
{
	t_env	*handle_edge_cases;

	(void)signal_received;
	(*handle_exit_status())->exit_status = 130;
	handle_edge_cases = *handle_t_env(NULL);
	if (handle_edge_cases->heredoc_mode)
	{
		(*handle_exit_status())->exit_status = 130;
		write(STDOUT_FILENO, "\n", 1);
		close(STDIN_FILENO);
		restore_normal_signals();
		return ;
	}
	else
		(*handle_t_env(NULL))->exit_timer++;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	if (handle_edge_cases->cat_flag == 0)
		rl_redisplay();
	else
		handle_edge_cases->cat_flag = 0;
}

void	setup_heredoc_signals(void)
{
	t_env	*env;

	env = *handle_t_env(NULL);
	if (env)
		env->heredoc_mode = 1;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_normal_signals(void)
{
	t_env	*env;

	env = *handle_t_env(NULL);
	if (env)
		env->heredoc_mode = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
