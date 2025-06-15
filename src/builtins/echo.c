/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:54:36 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/15 00:45:15 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (argv[0] == NULL)
	{
		ft_printf("\n");
		return ;
	}
	verify_flag(argv[1], &flag);
	if (flag)
		i++;
	while (argv[i])
	{
		if (i > 1)
			ft_printf(" ");
		ft_printf("%s", argv[i]);
		i++;
	}
	ft_printf("\n");
}
