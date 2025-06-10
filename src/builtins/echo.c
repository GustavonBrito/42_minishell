/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:54:36 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/10 19:50:44 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void echo(char *argv)
{
	int i;
	int flag;
	char **buffer;

	i = 0;
	buffer = ft_split(argv, ' ');
	if (buffer[1] == NULL)
	{
		printf("\n");
		return ;
	}
	else
		verify_flag(buffer[1], &flag);
	if (flag == 1)
		printf_without_n(buffer);
	else
	{
		while (buffer[++i])
		{
			if (i >= 2)
				printf(" ");
			printf("%s", buffer[i]);
		}
		printf("\n");
	}
}
