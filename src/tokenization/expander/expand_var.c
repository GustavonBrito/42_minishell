/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:03:33 by luiza             #+#    #+#             */
/*   Updated: 2025/08/03 21:13:20 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		expand_exit_status(char **res);
char	*itoa_exit_status(void);
int		expand_process_id(char **res);
char	*itoa_process_id(void);
int		expand_env_var(const char *str, char **res, int i_cmd);

int	expand_exit_status(char **res)
{
	char	*temp;

	temp = itoa_exit_status();
	if (!temp)
	{
		free(*res);
		*res = NULL;
		return (0);
	}
	*res = append_str(*res, temp);
	free(temp);
	if (!*res)
		return (0);
	return (1);
}

char	*itoa_exit_status(void)
{
	return (ft_itoa(g_exit_status));
}


int	expand_process_id(char **res)
{
	char	*temp;

	temp = itoa_process_id();
	if (!temp)
	{
		free(*res);
		*res = NULL;
		return (0);
	}
	*res = append_str(*res, temp);
	free(temp);
	if (!*res)
		return (0);
	return (1);
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

int	expand_env_var(const char *str, char **res, int i_cmd)
{
	char	var_input[256];
	int		i_var;
	char	*temp;
	int		start;

	start = i_cmd;
	i_var = 0;
	while (str[i_cmd] && (ft_isalnum(str[i_cmd]) || str[i_cmd] == '_'))
		var_input[i_var++] = str[i_cmd++];
	var_input[i_var] = '\0';
	temp = get_env_val(var_input);
	if (!temp)
	{
		free(*res);
		*res = NULL;
		return (0);
	}
	*res = append_str(*res, temp);
	free(temp);
	return (i_cmd - start);
}
