/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo <gustavo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:45:31 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/09/10 14:13:57 by gustavo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;
int	main(int argc, char **argv, char **env);

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	g_exit_status = 0;
	handle_store_env(env);
	shell_loop();
	free_env_list(*handle_t_env(NULL));
	rl_clear_history();
	return (0);
}
