/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:50:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/28 23:07:47 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_global = 0;

void sigint_handler(int sigint)
{
	(void) sigint;
	g_global = 1;
	printf("\n");
	rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void	shell_loop(void)
{
	char *buffer_received;
	char exit_shell[5] = "exit";
	
	signal(SIGINT, sigint_handler);
	while (1)
	{
		if (g_global == 1)
			buffer_received = readline("");
		else
		{
			buffer_received = readline("minishell$ ");
			g_global = 0;
		}
		if (ft_strncmp(buffer_received, exit_shell, 5) == 0)
			exit(0);
		if (buffer_received && *buffer_received)
			add_history(buffer_received);
		free(buffer_received);
		// if (read(0, buffer, BUFFER_SIZE) == 0) // verificar como parar com ctrl d
		// 	exit(0);
	}
}