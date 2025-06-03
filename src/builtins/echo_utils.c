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

int verify_flag(char *argv, t_builtins **builtins) // verificar se tem um traco depois do -n 
{
	int i;
	char **buffer;
	
	i = 0;
	buffer = ft_split(argv, ' ');
	if (buffer[1] == NULL)
		(*builtins)->flag = 0;
	else if (buffer[1][0] == '-' && buffer[1][1] == 'n')
	{
		while (buffer[1][++i])
		{
			if (buffer[1][i + 1] == ' ' || buffer[1][i + 1] == 'n' || buffer[1][i + 1] == '\0')
				(*builtins)->flag = 1;
			else
			{
				(*builtins)->flag = 0;
				break;
			}
		}
	}
	return (*builtins)->flag;	
}
