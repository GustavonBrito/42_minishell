/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:44:21 by gustavo           #+#    #+#             */
/*   Updated: 2025/09/18 06:23:38 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			init_pipe_struct(void);
t_pipe_mode		**handle_pipe_mode(void);
int				validate_pre_fork(t_command *cmd_crr, t_command *first_cmd);

void	init_pipe_struct(void)
{
	t_pipe_mode	*pipe;

	pipe = NULL;
	pipe = ft_calloc(1, sizeof(t_pipe_mode));
	*handle_pipe_mode() = pipe;
}

t_pipe_mode	**handle_pipe_mode(void)
{
	static t_pipe_mode	*pipe;

	return (&pipe);
}

void	free_pipe_mode(t_pipe_mode *head)
{
	free(head);
}

int	validate_pre_fork(t_command *cmd_crr, t_command *first_cmd)
{
	t_env	*env;

	env = (*handle_t_env(NULL));
	if (!cmd_crr || !cmd_crr->args || !cmd_crr->args[0])
	{
		g_exit_status = 1;
		flush_rsc_minishell(env, first_cmd, -1);
		return (-1);
	}
	if (ft_strncmp(cmd_crr->args[0], "cat", 3) == 0 && cmd_crr->args[1] == NULL)
		(*handle_t_env(NULL))->cat_flag = 1;
	return (0);
}
