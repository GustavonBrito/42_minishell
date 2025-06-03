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

void verify_flag(char *argv_splited, t_builtins **builtins) // verificar se tem um traco depois do -n 
{
	int i;
	
	i = 0;
	if (argv_splited[0] == '-' && argv_splited[1] == 'n')
	{
		while (argv_splited[++i])
		{
			if (argv_splited[i + 1] == ' ' || argv_splited[i + 1] == 'n' || argv_splited[i + 1] == '\0')
				(*builtins)->flag = 1;
			else
			{
				(*builtins)->flag = 0;
				break;
			}
		}
	}
}

void printf_without_n(char **buffer)
{
	printf("%s", buffer[1]);
}

