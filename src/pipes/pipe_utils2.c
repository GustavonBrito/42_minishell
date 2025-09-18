/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:44:21 by gustavo           #+#    #+#             */
/*   Updated: 2025/09/18 19:04:12 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			init_heredoc_struct(void);
void			init_pipe_struct(void);
t_heredoc		**handle_heredoc_redir(void);
t_pipe_mode		**handle_pipe_mode(void);
int				validate_pre_fork(t_command *cmd_crr, t_command *first_cmd);

void	init_heredoc_struct(void)
{
	t_heredoc	*heredoc;

	heredoc = NULL;
	heredoc = ft_calloc(1, sizeof(t_heredoc));
	*handle_heredoc_redir() = heredoc;
}
t_heredoc	**handle_heredoc_redir(void)
{
	static t_heredoc	*heredoc;

	return (&heredoc);
}

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
