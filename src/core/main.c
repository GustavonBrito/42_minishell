/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:45:31 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/09/18 19:23:39 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env);

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	handle_store_env(env);
	init_exit_struct();
	init_pipe_struct();
	init_heredoc_struct();
	shell_loop();
	free_env_list(*handle_t_env(NULL));
	rl_clear_history();
	return (0);
}
