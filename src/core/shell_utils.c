/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo <gustavo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 23:07:58 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/08/03 22:50:50 by gustavo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_exit_condition(char *buffer_received);
void	signal_handler(int signal);
char	*obtain_current_directory(void);
char	*get_env_or_cleanup(const char *var, char *to_free);

void	check_exit_condition(char *buffer_received)
{
	if (buffer_received == NULL)
	{
		ft_printf("exit\n");
		rl_clear_history();
		free_env_list(*handle_t_env(NULL));
		exit(0);
	}
}

void	signal_handler(int signal)
{
	(void)signal;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}

char	*obtain_current_directory(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
		return (NULL);
	return (dir);
}

char	*get_env_or_cleanup(const char *var, char *to_free)
{
	char	*value;

	value = getenv(var);
	if (!value)
	{
		free(to_free);
		return (NULL);
	}
	return (value);
}
