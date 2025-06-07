/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:50:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/07 00:43:37 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	shell_loop(void)
{
	char	*buffer_received;
	//int		/*last_exit*/;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	///*last_exit*/ = 0;
	while (1)
	{
		buffer_received = readline("minishell$ ");
		check_exit_condition(buffer_received);
		if (*buffer_received)
		{
			add_history(buffer_received);
			process_input(buffer_received/*, last_exit*/);
			// to-do: updt /*last_exit*/ accordingly (related to $?)
		}
		free(buffer_received);
	}
}
