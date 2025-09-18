/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:50:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/09/18 01:37:59 by lukorman         ###   ########.fr       */


#include "minishell.h"

void		shell_loop(void);
static char	*create_prompt(void);
static char	*format_path(char *current_dir, char *home_dir);
static char	*build_prompt(char *username, char *display_path);

void	shell_loop(void)
{
	char	*buffer_received;
	char	*prompt;
	char	*colored_prompt;
	char	*tmp;
	t_env	*env;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		env = *handle_t_env(NULL);
		if (env)
			env->heredoc_mode = 0;
		prompt = create_prompt();
		if (!prompt)
			return ;
		env->pipe = NULL;
		colored_prompt = ft_strjoin("\001\033[0;32m\002", prompt);
		tmp = colored_prompt;
		colored_prompt = ft_strjoin(colored_prompt, "\001\033[0m\002");
		free(tmp);
		buffer_received = readline(colored_prompt);
		free(prompt);
		free(colored_prompt);
		check_exit_condition(buffer_received);
		if (*buffer_received)
		{
			add_history(buffer_received);
			g_exit_status = process_input(buffer_received);
		}
		free(buffer_received);
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
}

static char	*create_prompt(void)
{
	char	*current_dir;
	char	*username;
	char	*home_dir;
	char	*display_path;
	char	*prompt;

	current_dir = obtain_current_directory();
	if (!current_dir)
		return (NULL);
	username = get_env_or_cleanup("USER", current_dir);
	if (!username)
		return (NULL);
	home_dir = getenv("HOME");
	display_path = format_path(current_dir, home_dir);
	if (!display_path)
	{
		free(current_dir);
		return (NULL);
	}
	prompt = build_prompt(username, display_path);
	free(current_dir);
	if (display_path != current_dir)
		free(display_path);
	return (prompt);
}

static char	*format_path(char *current_dir, char *home_dir)
{
	char	*relative_path;
	char	*display_path;
	int		home_len;

	if (!home_dir)
		return (current_dir);
	home_len = ft_strlen(home_dir);
	if (ft_strncmp(current_dir, home_dir, home_len) != 0)
		return (current_dir);
	if (current_dir[home_len] == '\0')
		return (ft_strdup("~"));
	if (current_dir[home_len] == '/')
	{
		relative_path = current_dir + home_len + 1;
		display_path = ft_strjoin("~/", relative_path);
		return (display_path);
	}
	return (current_dir);
}

static char	*build_prompt(char *username, char *display_path)
{
	char	*return_path;
	char	*full_prompt;

	return_path = ft_strjoin(username, "@minishell:");
	if (!return_path)
		return (NULL);
	full_prompt = ft_strjoin(return_path, display_path);
	free(return_path);
	if (!full_prompt)
		return (NULL);
	return_path = ft_strjoin(full_prompt, "$ ");
	free(full_prompt);
	return (return_path);
}
