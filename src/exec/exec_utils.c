/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:54:17 by luiza             #+#    #+#             */
/*   Updated: 2025/08/03 19:27:16 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cleanup_failed_env_array(char **env_array, int filled_count);
void	cleanup_n_exit(char **env_array, char *cmd_path);
void	free_env_array(char **env_array);

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
