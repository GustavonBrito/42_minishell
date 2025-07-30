/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 06:28:59 by luiza             #+#    #+#             */
/*   Updated: 2025/07/30 17:15:38 by luiza            ###   ########.fr       */
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
	exit(exit_code);
}
