/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:50:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/04 17:57:52 by luiza            ###   ########.fr       */
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
		if (buffer_received == NULL)
			exit(0);
		if (ft_strncmp(buffer_received, exit_shell, 5) == 0)
		{
			free(buffer_received);
			exit(0);
		}
		//if (*buffer_received)
		//{
			add_history(buffer_received);
		//	process_input(buffer_received);
		//}
		free(buffer_received);
	}
}
