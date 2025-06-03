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

void is_builtin(char *builtin)
{
	builtin = ft_strtrim(builtin, " ");
	
	if (ft_strncmp(builtin, "echo", 4) == 0)
		echo(builtin);
	else if (ft_strlen(builtin) == 2 && ft_strncmp(builtin, "cd", 2) == 0)
		printf("yep");
	else if (ft_strlen(builtin) == 3 && ft_strncmp(builtin, "pwd", 3) == 0)
		printf("yep");
	else if (ft_strlen(builtin) == 6 && ft_strncmp(builtin, "export", 6) == 0)
		printf("yep");
	else if (ft_strlen(builtin) == 5 && ft_strncmp(builtin, "unset", 5) == 0)
		printf("yep");
	else if (ft_strlen(builtin) == 3 && ft_strncmp(builtin, "env", 3) == 0)
		printf("yep");
	else if (ft_strlen(builtin) == 4 && ft_strncmp(builtin, "exit", 4) == 0)
		printf("yep");
	else
		printf("nenhum valor corresponde");
}

