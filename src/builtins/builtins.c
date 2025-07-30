/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 23:04:27 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/29 20:58:23 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_builtin(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (ft_strncmp(cmd->args[0], "echo", 4) == 0
		&& ft_strlen(cmd->args[0]) == 4)
		echo(cmd);
	else if (ft_strncmp(cmd->args[0], "cd", 2) == 0
		&& ft_strlen(cmd->args[0]) == 2)
		cd(cmd);
	else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0
		&& ft_strlen(cmd->args[0]) == 3)
		pwd();
	else if (ft_strncmp(cmd->args[0], "export", 6) == 0
		&& ft_strlen(cmd->args[0]) == 6)
		export(cmd);
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0
		&& ft_strlen(cmd->args[0]) == 5)
		unset(cmd);
	else if (ft_strncmp(cmd->args[0], "env", 3) == 0
		&& ft_strlen(cmd->args[0]) == 3)
		env(0);
	else if (ft_strncmp(cmd->args[0], "exit", 4) == 0
		&& ft_strlen(cmd->args[0]) == 4)
		exit_minishell(cmd);
}
