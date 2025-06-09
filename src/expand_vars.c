/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:03:33 by luiza             #+#    #+#             */
/*   Updated: 2025/06/08 22:29:46 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			expand_variables(t_command *cmd);
static char	*expand_str(const char *str, int expand_check);
static char	*itoa_exit_status(void);
static char	*append_str(char *dest, const char *src);
static char	*itoa_process_id(void);
static char	*get_env_val(const char *var_name);
static char	*append_char(char *dest, char c);

int	expand_variables(t_command *cmd)
{
	int		i;
	char	*expand;
	int		expand_check;

	i = 0;
	while (cmd->args[i])
	{
		expand_check = (cmd->token_types && cmd->token_types[i] != SINGLE_QUOTE);
		expand = expand_str(cmd->args[i], expand_check);
		if (!expand)
			return (report_error("memory allocation error", 1));
		free(cmd->args[i]);
		cmd->args[i] = expand;
		i++;
	}
	return (0);
}

static char	*expand_str(const char *str, int expand_check)
{
	char	*res;
	char	var_input[256];
	int		i_cmd;
	int		i_var;
	char	*temp;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	i_cmd = 0;
	while (str[i_cmd])
	{
		if (str[i_cmd] == '$' && expand_check)
		{
			i_cmd++;
			if (str[i_cmd] == '?')
			{
				temp = itoa_exit_status();
				if (!temp)
				{
					free(res);
					return (NULL);
				}
				res = append_str(res, temp);
				free(temp);
				if (!res)
					return (NULL);
				i_cmd++;
			}
			else if (str[i_cmd] == '$')
			{
				temp = itoa_process_id();
				if (!temp)
				{
					free(res);
					return (NULL);
				}
				res = append_str(res, temp);
				free(temp);
				if (!res)
					return (NULL);
				i_cmd++;
			}
			else if (str[i_cmd] && (ft_isalpha(str[i_cmd]) || str[i_cmd] == '_'))
			{
				i_var = 0;
				while (str[i_cmd] && (ft_isalnum(str[i_cmd]) || str[i_cmd] == '_'))
					var_input[i_var++] = str[i_cmd++];
				var_input[i_var] = '\0';
				temp = get_env_val(var_input);
				if (!temp)
				{
					free(res);
					return (NULL);
				}
				res = append_str(res, temp);
				free(temp);
				if (!res)
					return (NULL);
			}
			else
				res = append_char(res, '$');
		}
		else
		{
			res = append_char(res, str[i_cmd++]);
			if (!res)
				return (NULL);
		}
	}
	return (res);
}

static char	*itoa_process_id(void)
{
	return (ft_itoa(getpid()));
}

static char	*itoa_exit_status(void)
{
	return (ft_itoa(g_exit_status));
}

static char	*append_str(char *dest, const char *src)
{
	char	*new_str;
	size_t	new_len;

	if (!dest || !src)
		return (NULL);
	new_len = ft_strlen(dest) + ft_strlen(src);
	new_str = malloc(new_len + 1);
	if (!new_str)
		return (NULL);
	new_str[0] = '\0';
	ft_strlcat(new_str, dest, new_len + 1);
	ft_strlcat(new_str, src, new_len + 1);
	free(dest);
	return (new_str);
}

static char	*get_env_val(const char *var_name)
{
	char	*value;

	value = getenv(var_name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static char	*append_char(char *dest, char c)
{
	char	*new_str;
	size_t	len;

	if (!dest)
		return (NULL);
	len = ft_strlen(dest);
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	new_str[0] = '\0';
	ft_strlcat(new_str, dest, len + 2);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(dest);
	return (new_str);
}
