/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo <gustavo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 06:28:59 by luiza             #+#    #+#             */
/*   Updated: 2025/08/03 21:47:41 by gustavo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		report_error(const char *msg, int exit_code);
void	critical_error(const char *msg, int exit_code);
void	write_err(const char *msg);

void	write_err(const char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
}

int	report_error(const char *msg, int exit_code)
{
	ft_printf("minishell: %s\n", msg);
	return (exit_code);
}

void	critical_error(const char *msg, int exit_code)
{
	ft_printf("minishell: %s\n", msg);
	free_env_list(*handle_t_env(NULL));
	exit(exit_code);
}
