/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 05:45:32 by gserafio          #+#    #+#             */
/*   Updated: 2025/09/18 19:41:20 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		analyze_exit_args(t_command *cmd, int arg_count);
void	cleanup_and_exit(int exit_code, t_command *cmd);

int	analyze_exit_args(t_command *cmd, int arg_count)
{
	if (!is_valid_number(cmd->args[1]))
	{
		write(2, "minishell: exit: numeric argument required\n", 43);
		(*handle_exit_status())->exit_status = 2;
		flush_rsc_minishell((*handle_t_env(NULL)), cmd,
			(*handle_exit_status())->exit_status);
		free_env_list(*handle_t_env(NULL));
		rl_clear_history();
		exit((*handle_exit_status())->exit_status);
	}
	else if (arg_count > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		(*handle_exit_status())->exit_status = 1;
		return (1);
	}
	return (0);
}

void	cleanup_and_exit(int exit_code, t_command *cmd)
{
	flush_rsc_minishell((*handle_t_env(NULL)), cmd, exit_code);
	free_env_list(*handle_t_env(NULL));
	rl_clear_history();
	exit(exit_code);
}
