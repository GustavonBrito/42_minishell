/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 23:04:27 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/15 01:36:26 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norminette:+25 lines needs to be chopped
void	is_builtin(char **argv)
{
	if (!argv || !argv[0])
		return ;
	if (ft_strncmp(argv[0], "echo", 4) == 0 && (argv[0][4] == ' '
		|| argv[0][4] == '\0'))
		echo(argv);
	else if (ft_strncmp(argv[0], "cd", 2) == 0 && (argv[0][2] == ' '
		|| argv[0][2] == '\0'))
		cd(argv);
	else if (ft_strncmp(argv[0], "pwd", 3) == 0 && (argv[0][3] == ' '
		|| argv[0][3] == '\0'))
		pwd();
	else if (ft_strncmp(argv[0], "export", 6) == 0 && (argv[0][6] == ' '
		|| argv[0][6] == '\0'))
		export(argv);
	else if (ft_strncmp(argv[0], "unset", 5) == 0 && (argv[0][5] == ' '
		|| argv[0][5] == '\0'))
		unset(argv);
	else if (ft_strncmp(argv[0], "env", 3) == 0 && (argv[0][3] == ' '
		|| argv[0][3] == '\0'))
		env(0);
	else if (ft_strncmp(argv[0], "exit", 4) == 0 && (argv[0][4] == ' '
		|| argv[0][4] == '\0'))
		exit_minishell();
	else
		return ;
}
