/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:26:54 by lukorman          #+#    #+#             */
/*   Updated: 2025/09/14 21:09:17 by lukorman         ###   ########.fr       */
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
	handle_edge_cases = *handle_t_env(NULL);
	if (handle_edge_cases && handle_edge_cases->heredoc_mode)
	{
		ft_printf("\n");
		g_exit_status = 130;
		return ;
	}
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_exit_status = 130;
	if (handle_edge_cases->cat_flag == 0)
		rl_redisplay();
	else
		handle_edge_cases->cat_flag = 0;
}

void setup_heredoc_signals(void)
{
	t_env *env;

	env= *handle_t_env(NULL);
	if (env)
		env->heredoc_mode = 1;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void restore_normal_signals(void)
{
	t_env *env;

	env = *handle_t_env(NULL);
	if (env)
		env->heredoc_mode = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
