/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:50:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/09 23:59:26 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	shell_loop(void);

char	*obtain_current_directory(char **dir_extracted, char *current_directory)
{
	const char *relative_path;
	char		*user_path;
	int			user_length;
	int			relative_path_length;
	int i;

	i = -1;
	while (dir_extracted[++i])
	{
		if (ft_strncmp(dir_extracted[i], getenv("USER"), ft_strlen(getenv("USER"))) == 0)
		{
			i++;
			break;
		}
	}
	relative_path = ft_strnstr(current_directory, dir_extracted[i], ft_strlen(current_directory));
	relative_path_length = ft_strlen(relative_path);
	user_length = ft_strlen(getenv("USER"));
	user_path = malloc(sizeof(char) * relative_path_length + user_length + 14);
	ft_strlcpy(user_path, (const char *)getenv("USER"), user_length + 1);
	ft_strlcat(user_path, "@minishell:~/", user_length + 14);
	user_length = ft_strlen(user_path);
	ft_strlcat(user_path, relative_path, user_length + relative_path_length + 1);
	user_length = ft_strlen(user_path);
	ft_strlcat(user_path, " ", user_length + 2);
	return (user_path);
}

void	shell_loop(void)
{
	char	*buffer_received;
	char 	*current_directory;
	char	**directory_splited;
	const char	*relative_path;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		current_directory = getcwd(NULL, 0);
		if (!current_directory)
			free(current_directory);
		directory_splited = ft_split(current_directory, '/');
		relative_path = obtain_current_directory(directory_splited, current_directory);
		buffer_received = readline((const char *)relative_path);
		check_exit_condition(buffer_received);
		if (*buffer_received)
		{
			add_history(buffer_received);
			process_input(buffer_received);
			is_builtin(buffer_received);
		}
		free(buffer_received);
		free(current_directory);
	}
}
