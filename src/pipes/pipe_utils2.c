/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo <gustavo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:44:21 by gustavo           #+#    #+#             */
/*   Updated: 2025/09/17 13:56:38 by gustavo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			init_pipe_struct(void);
t_pipe_mode		**handle_pipe_mode(void);

void	init_pipe_struct(void)
{
	t_pipe_mode *pipe;
	
	pipe = NULL;
	pipe = ft_calloc(1, sizeof(t_pipe_mode));
	*handle_pipe_mode() = pipe;
}

t_pipe_mode	**handle_pipe_mode(void)
{
	static t_pipe_mode	*pipe;
	return (&pipe);
}
void		free_pipe_mode(t_pipe_mode *head)
{
	free(head);
}