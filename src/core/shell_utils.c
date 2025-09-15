/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 23:07:58 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/09/14 12:14:53 by gustavo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_exit_condition(char *buffer_received);
char	*obtain_current_directory(void);
char	*get_env_or_cleanup(const char *var, char *to_free);
void	initialize_arrays(t_command *cmd, int arg_count);

void	check_exit_condition(char *buffer_received)
{
	if (buffer_received == NULL)
	{
		ft_printf("exit\n");
		(*(handle_t_env(NULL)))->cat_flag = 0;
		rl_clear_history();
		free_env_list(*handle_t_env(NULL));
		exit(0);
	}
}

char	*obtain_current_directory(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
		return (NULL);
	return (dir);
}

char	*get_env_or_cleanup(const char *var, char *to_free)
{
	char	*value;

	value = getenv(var);
	if (!value)
	{
		free(to_free);
		return (NULL);
	}
	return (value);
}

void	initialize_arrays(t_command *cmd, int arg_count)
{
	int	i;

	i = 0;
	while (i <= arg_count)
	{
		cmd->args[i] = NULL;
		cmd->quote_removed[i] = 0;
		cmd->token_types[i] = WORD;
		i++;
	}
}
