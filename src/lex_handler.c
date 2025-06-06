/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:21:55 by luiza             #+#    #+#             */
/*   Updated: 2025/06/05 01:45:17 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			handle_quotes(char *input, t_token **token_lst, int i);
int			handle_var(char *input, t_token **token_lst, int i);
static int	process_quote(char *input, t_token **token_lst, int start, char quote_type);
static int	process_var_name(char *input, t_token **token_lst, int start);
static int	handle_special_vars(char *input, t_token **token_lst, int i);

int	handle_quotes(char *input, t_token **token_lst, int i)
{
	char	quote_type;
	int		start;

	quote_type = input[i];
	start = i + 1;
	i++;
	while (input[i] && input[i] != quote_type)
		i++;
	if (!input[i])
	{
		ft_printf("minishell: syntax error: unclosed quote\n");
		return (1);
	}
	return (process_quote(input, token_lst, start, quote_type));
}

int	handle_var(char *input, t_token **token_lst, int i)
{
	int	start;

	start = i;
	i++;
	if (input[i] == '?' || input[i] == '$')
		return (handle_special_vars(input, token_lst, i - 1));
	if (!ft_isalpha(input[i]) && input[i] != '_')
	{
		add_token(token_lst, "$", WORD);
		return (1);
	}
	return (process_var_name(input, token_lst, start));
}

static int	process_quote(char *input, t_token **token_lst, int start, char quote_type)
{
	int		i;
	int		len;
	char	*content;

	i = start;
	while (input[i] && input[i] != quote_type)
		i++;
	len = i - start;
	content = ft_substr(input, start, len);
	if (!content)
		return (len + 2);
	if (quote_type == '\'')
		add_token(token_lst, content, SINGLE_QUOTE);
	else
		add_token(token_lst, content, DOUBLE_QUOTE);
	free(content);
	return (len + 2);
}

static int	process_var_name(char *input, t_token **token_lst, int start)
{
	int		i;
	int		len;
	char	*var_name;

	i = start + 1;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		i++;
	len = i - start;
	var_name = ft_substr(input, start, len);
	if (!var_name)
		return (len);
	add_token(token_lst, var_name, VAR);
	free(var_name);
	return (len);
}

static int	handle_special_vars(char *input, t_token **token_lst, int i)
{
	if (input[i + 1] == '?')
	{
		add_token(token_lst, "$?", VAR);
		return (2);
	}
	if (input[i + 1] == '$')
	{
		add_token(token_lst, "$$", VAR);
		return (2);
	}
	return (1);
}
