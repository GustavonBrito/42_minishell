/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:03:33 by luiza             #+#    #+#             */
/*   Updated: 2025/08/03 21:12:58 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_str(char *dest, const char *src);
char	*get_env_val(const char *var_name);
char	*append_char(char *dest, char c);
int		handle_regular_char(const char *str, char **res, int i);

char	*append_str(char *dest, const char *src)
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

char	*get_env_val(const char *var_name)
{
	char	*value;

	value = getenv(var_name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*append_char(char *dest, char c)
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

int	handle_regular_char(const char *str, char **res, int i)
{
	*res = append_char(*res, str[i]);
	if (!*res)
		return (0);
	return (1);
}
