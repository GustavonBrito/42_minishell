/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 23:07:58 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/07 06:12:29 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_exit_condition(char *buffer_received)
{
	char	*trimmed;

	if (buffer_received == NULL)
	{
		ft_printf("exit\n");
		exit(0);
	}
	trimmed = ft_strtrim(buffer_received, " ");
	if (!trimmed)
		return ;
	if (ft_strlen(trimmed) == 4 && ft_strncmp(trimmed, "exit", 4) == 0)
	{
		free(trimmed);
		ft_printf("exit\n");
		exit(0);
	}
	free(trimmed);
}

void	signal_handler(int signal)
{
	(void)signal;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
