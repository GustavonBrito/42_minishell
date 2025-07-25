/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:29:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/15 01:04:52 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	verify_flag(char *argv_splited, int *flag)
{
	int	i;

	i = 0;
	if (argv_splited[0] == '-' && argv_splited[1] == 'n')
	{
		while (argv_splited[++i])
		{
			if (argv_splited[i + 1] == ' ' || argv_splited[i + 1] == 'n'
				|| argv_splited[i + 1] == '\0')
				*flag = 1;
			else
			{
				*flag = 0;
				break ;
			}
		}
	}
}

/* void	printf_without_n(char **buffer)
{
	int	i;

	i = 1;
	while (1)
	{
		if (ft_strnstr(buffer[i], "-n", ft_strlen(buffer[i])) != 0)
			i++;
		else
		{
			ft_printf("%s", buffer[i]);
			break ;
		}
	}
} */
