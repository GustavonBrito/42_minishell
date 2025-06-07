/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 06:28:59 by luiza             #+#    #+#             */
/*   Updated: 2025/06/07 06:29:55 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
