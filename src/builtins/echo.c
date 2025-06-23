/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:54:36 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/19 19:43:04 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **argv)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (argv[1] == NULL)
	{
		ft_printf("\n");
		return ;
	}
	verify_flag(argv[1], &flag);
	if (flag)
		printf_without_n(argv);
	else
	{
		while (argv[++i])
		{
			if (i > 1)
				ft_printf(" ");
			ft_printf("%s", argv[i]);
		}
		ft_printf("\n");
	}
}
