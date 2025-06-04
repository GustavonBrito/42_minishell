/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:50:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/04 18:11:21 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	shell_loop(void)
{
	char *buffer_received;
	char exit_shell[5] = "exit";

	signal(SIGINT, sigint_handler);
	char	*buffer_received;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		buffer_received = readline("minishell$ ");
		check_exit_condition(buffer_received);
		if (*buffer_received)
			add_history(buffer_received);
		//	process_input(buffer_received);
		//}
		free(buffer_received);
	}
}
