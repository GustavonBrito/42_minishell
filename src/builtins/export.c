/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:28 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/14 22:45:35 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void export(char *argv)
{
	char **buffer;
	char **sub_buffer;

	buffer = ft_split(argv, ' ');
	if (buffer[1] == NULL)
		env(1);
	else
	{
		sub_buffer = ft_split(buffer[1], '=');
		setenv(sub_buffer[0], sub_buffer[1], 1);
		ft_printf("Created env %s\n", getenv(sub_buffer[0]));
	}
}
