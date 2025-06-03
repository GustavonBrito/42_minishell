/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:29:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/02 22:53:15 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void verify_flag(char *argv, t_builtins **builtins) // verificar se tem um traco depois do -n 
{
	int i;
	char **buffer;
	
	i = -1;
	buffer = ft_split(argv, ' ');
	while (buffer[++i])
	{
		if (i == 1 && ft_strncmp(buffer[i], "-n", 2) == 0)
			break;
		else
			(*builtins)->flag = 0;
	}
	i = -1;
	while (buffer[1][++i])
	{
		if (buffer[1][i] == '-' && buffer[1][i + 1] == 'n' && (buffer[1][i + 2] == 32 || buffer[1][i + 2] != 32))
		{
			(*builtins)->flag = 1;
			break;
		}
		else
			break;
	}
}
