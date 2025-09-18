/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:26:20 by gserafio          #+#    #+#             */
/*   Updated: 2025/09/18 14:27:03 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_user_input(t_env *env)
{
	char	*prompt;
	char	*colored_prompt;
	char	*tmp;
	char	*buffer;

	env->pipe = NULL;
	prompt = create_prompt();
	if (!prompt)
		return (NULL);
	colored_prompt = ft_strjoin("\001\033[0;32m\002", prompt);
	tmp = colored_prompt;
	colored_prompt = ft_strjoin(colored_prompt, "\001\033[0m\002");
	free(tmp);
	buffer = readline(colored_prompt);
	free(prompt);
	free(colored_prompt);
	return (buffer);
}

static void	process_user_input(char *buffer)
{
	if (!buffer)
		check_exit_condition(buffer);
	if (*buffer)
	{
		add_history(buffer);
		g_exit_status = process_input(buffer);
	}
	free(buffer);
	if (g_exit_status != 0)
	{
		if ((*handle_t_env(NULL))->exit_timer == 1)
		{
			(*handle_t_env(NULL))->exit_timer = 0;
			g_exit_status = 0;
		}
		else
			(*handle_t_env(NULL))->exit_timer++;
	}
}
