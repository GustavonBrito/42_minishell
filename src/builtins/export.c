/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:28 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/10 00:45:16 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void export(char *argv)
{
	int j;
	int i;
	char **buffer;
	char **sub_buffer;
	
	i = -1;
	buffer = ft_split(argv, ' ');
	while(buffer[++i])
	{
		j = -1;
		while (buffer[i][++j])
		{
			if (buffer[i][++j + 1] == '=')
			{
				sub_buffer = ft_split(buffer[1],  '=');
				break;
			}
		}
		if (buffer[i][++j + 1] == '=')
			break;
	}
	setenv(sub_buffer[0], sub_buffer[1], 1);
	printf("Env criada agora %s", getenv(sub_buffer[0]));
}