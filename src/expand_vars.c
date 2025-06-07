/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:03:33 by luiza             #+#    #+#             */
/*   Updated: 2025/06/07 00:40:29 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		expand_variables(t_command *cmd/*, int last_exit*/);
static char	*expand_str(const char *str/*, int last_exit*/);
//static char	*itoa_exit_status(int status);
static char	*append_str(char *dest, const char *src);
static char	*get_env_val(const char *name);
static char	*append_char(char *dest, char c);

void	expand_variables(t_command *cmd/*, int last_exit*/)
{
	int		i;
	char	*expand;

	i = 0;
	while (cmd->args[i])
	{
		expand = expand_str(cmd->args[i]/*, last_exit*/);
		free(cmd->args[i]);
		cmd->args[i] = expand;
		i++;
	}
}

static char	*expand_str(const char *str/*, int last_exit*/)
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
		if (str[i_cmd] == '$')
		{
			i_cmd++;
			if (str[i_cmd] == '?')
			{
				//temp = itoa_exit_status(/*last_exit*/);
				res = append_str(res, temp);
				free(temp);
				i_cmd++;
			}
			else if (str[i_cmd] && (ft_isalpha(str[i_cmd]) || str[i_cmd] == '_'))
			{
				i_var = 0;
				while (str[i_cmd] && (ft_isalnum(str[i_cmd]) || str[i_cmd] == '_'))
					var_input[i_var++] = str[i_cmd++];
				var_input[i_var] = '\0';
				temp = get_env_val(var_input);
				res = append_str(res, temp);
				free(temp);
			}
			else
				res = append_char(res, '$');
		}
		else
			res = append_char(res, str[i_cmd++]);
	}
	return (res);
}

/* static char	*itoa_exit_status(int status)
{
	return (ft_itoa(status));
} */

static char	*append_str(char *dest, const char *src)
{
	char	*new_str;
	size_t	new_len;

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

static char	*get_env_val(const char *name)
{
	char	*value;

	value = getenv(name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static char	*append_char(char *dest, char c)
{
	char	*new_str;
	size_t	len;

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
