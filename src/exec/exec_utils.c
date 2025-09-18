/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:54:17 by luiza             #+#    #+#             */
/*   Updated: 2025/09/18 07:42:10 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_parent_process(pid_t pid);
char	**cleanup_failed_env_array(char **env_array, int filled_count);
void	cleanup_n_exit(char **env_array, char *cmd_path);
void	free_env_array(char **env_array);

int	handle_parent_process(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		(*(handle_t_env(NULL)))->cat_flag = 0;
		return (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			write(2, "Quit (core dumped)\n", 20);
			(*(handle_t_env(NULL)))->cat_flag = 0;
		}
		return (128 + WTERMSIG(status));
	}
	return (status);
}

char	**cleanup_failed_env_array(char **env_array, int filled_count)
{
	while (--filled_count >= 0)
		free(env_array[filled_count]);
	free(env_array);
	return (NULL);
}

void	cleanup_n_exit(char **env_array, char *cmd_path)
{
	free_env_array(env_array);
	free(cmd_path);
	exit(126);
}

void	free_env_array(char **env_array)
{
	int	i;

	if (!env_array)
		return ;
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}
