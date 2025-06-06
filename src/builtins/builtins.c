/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 23:04:27 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/06 14:25:33 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void is_builtin(char *argv)
{
	t_builtins *builtins;
	argv = ft_strtrim(argv, " ");
	
	builtins = (t_builtins *)malloc(sizeof(t_builtins));
	builtins->flag = 0;
	if (ft_strncmp(argv, "echo", 4) == 0 && (argv[4] == ' ' || argv[4] == '\0'))
		echo(argv, &builtins);
	else if (ft_strncmp(argv, "cd", 2) == 0 && (argv[2] == ' ' || argv[2] == '\0'))
		cd(argv, &builtins);
	else if (ft_strncmp(argv, "pwd", 3) == 0 && (argv[3] == ' ' || argv[3] == '\0'))
		pwd();
	else if (ft_strncmp(argv, "export", 6) == 0 && (argv[6] == ' ' || argv[6] == '\0'))
		export();
	else if (ft_strncmp(argv, "unset", 5) == 0 && (argv[5] == ' ' || argv[5] == '\0'))
		unset();
	else if (ft_strncmp(argv, "env", 3) == 0 && (argv[3] == ' ' || argv[3] == '\0'))
		env();
	else if (ft_strncmp(argv, "exit", 4) == 0 && (argv[4] == ' ' || argv[4] == '\0'))
		exit_minishell();
	else
		printf("nenhum valor corresponde");
}

