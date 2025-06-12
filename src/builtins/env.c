/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/11 11:29:11 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void env(void)
{
	extern char **environ;
	int i;

	i = -1;
	while (environ[++i])
	{
		printf("%s\n", environ[i]);
	}
}