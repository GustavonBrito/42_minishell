/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 23:04:27 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/01 23:35:29 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void is_builtin(char *argv)
{
	t_builtins *builtins;
	argv = ft_strtrim(argv, " ");
	
	builtins = (t_builtins *)malloc(sizeof(t_builtins));
	builtins->flag = 0;
	if (ft_strncmp(argv, "echo", 4) == 0)
		echo(argv, &builtins);
	else if (ft_strlen(argv) == 2 && ft_strncmp(argv, "cd", 2) == 0)
		printf("yep");
	else if (ft_strlen(argv) == 3 && ft_strncmp(argv, "pwd", 3) == 0)
		printf("yep");
	else if (ft_strlen(argv) == 6 && ft_strncmp(argv, "export", 6) == 0)
		printf("yep");
	else if (ft_strlen(argv) == 5 && ft_strncmp(argv, "unset", 5) == 0)
		printf("yep");
	else if (ft_strlen(argv) == 3 && ft_strncmp(argv, "env", 3) == 0)
		printf("yep");
	else if (ft_strlen(argv) == 4 && ft_strncmp(argv, "exit", 4) == 0)
		printf("yep");
	else
		printf("nenhum valor corresponde");
}

