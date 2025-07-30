/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:45:31 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/29 21:09:19 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;
int	main(int argc, char **argv, char **env);

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	g_exit_status = 0;
	handle_store_env(env);
	shell_loop();
	return (0);
}
