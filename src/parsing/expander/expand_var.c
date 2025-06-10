/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:03:33 by luiza             #+#    #+#             */
/*   Updated: 2025/06/09 00:04:42 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	return (ft_itoa(getpid()));
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
