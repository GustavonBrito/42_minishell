/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:39:52 by luiza             #+#    #+#             */
/*   Updated: 2025/06/10 00:12:29 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		free_commands(t_command *cmd);
static void	free_redirections(t_redir *redirs);

void	free_commands(t_command *cmd)
{
	t_command	*temp;
	int		i;
	while (cmd)
	{
		temp = cmd->next;
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				free(cmd->args[i]);
				i++;
			}
			free(cmd->args);
		}
		free_redirections(cmd->redirs);
		free(cmd);
		cmd = temp;
	}
}

static void	free_redirections(t_redir *redirs)
{
	t_redir	*temp;

	while (redirs)
	{
		temp = redirs->next;
		free(redirs->file);
		free(redirs);
		redirs = temp;
	}
}
