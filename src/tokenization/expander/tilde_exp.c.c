/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_exp.c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:03:33 by luiza             #+#    #+#             */
/*   Updated: 2025/08/03 22:25:49 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			handle_tilde_expansion(const char *str, char **res, int i_cmd);
static int	handle_no_home_env(char **res);
static int	exp_tilde_path(const char *str, char **res, int i_cmd, int start);
char		*remove_quotes(char *str);
char		*itoa_process_id(void);

int	handle_tilde_expansion(const char *str, char **res, int i_cmd)
{
	char	*home;
	int		start;

	start = i_cmd;
	home = getenv("HOME");
	if (!home)
		return (handle_no_home_env(res));
	if (str[i_cmd + 1] == '\0' || str[i_cmd + 1] == '/')
		return (exp_tilde_path(str, res, i_cmd, start));
	return (append_literal_tilde(res));
}

static int	handle_no_home_env(char **res)
{
	*res = append_char(*res, '~');
	if (!*res)
		return (0);
	return (1);
}

static int	exp_tilde_path(const char *str, char **res, int i_cmd, int start)
{
	char	*home;

	home = getenv("HOME");
	*res = append_str(*res, home);
	if (!*res)
		return (0);
	i_cmd++;
	if (str[i_cmd] == '/')
		i_cmd = append_remaining_path(str, res, i_cmd);
	return (i_cmd - start);
}

char	*remove_quotes(char *str)
{
	int		len;
	char	*result;

	if (!str)
		return (str);
	len = ft_strlen(str);
	if (len == 0)
		return (str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	return (process_quote_rm(str, result));
}

char	*itoa_process_id(void)
{
	int		fd;
	ssize_t	read_return;
	char	buffer[8];
	char	**buffer_splitted;
	char	*result;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		return (NULL);
	read_return = read(fd, buffer, sizeof(buffer) - 1);
	close(fd);
	if (read_return == -1)
		return (NULL);
	buffer[read_return] = '\0';
	buffer_splitted = ft_split(buffer, ' ');
	if (!buffer_splitted || !buffer_splitted[0])
		return (NULL);
	result = ft_strdup(buffer_splitted[0]);
	ft_free_split(buffer_splitted);
	return (result);
}
