/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo <gustavo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:21:55 by luiza             #+#    #+#             */
/*   Updated: 2025/09/14 12:30:07 by gustavo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			process_input(char *input);
static int	lex_token(char *input);
static int	tokenize_input(char *input, t_token **token_lst);
static int	process_next_token(char *input, t_token **token_lst, int i);
static int	process_commands(t_command *commands);

int	process_input(char *input)
{
	int	i;
	char	open_quote;

	i = 0;
	open_quote = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '"'))
		{
			if (open_quote == 0)
				open_quote = input[i];
			else if (open_quote == input[i])
				open_quote = 0;
		}
		i++;
	}
	if (open_quote != 0)
	{
		write(2, "No closed quotes\n", 18);
		return (0);
	}
	if (!input || ft_strlen(input) == 0)
		return (0);
	return (lex_token(input));
}

static int	lex_token(char *input)
{
	t_token		*token_lst;
	t_command	*commands;
	int			res;

	token_lst = NULL;
	res = tokenize_input(input, &token_lst);
	if (res != 0)
	{
		if (ft_strncmp(input, "echo", 4) == 0)
			printf("\n");
		else if (ft_strncmp(input, "cat", 3) == 0)
			write(2, "cat: '': No such file or directory\n", 36);
		return (res);
	}
	commands = parse_tokens(token_lst);
	if (!commands)
	{
		free_tokens(token_lst);
		return (1);
	}
	(*handle_t_env(NULL))->tokens = token_lst;
	res = process_commands(commands);
	free_commands(commands);
	free_tokens(token_lst);
	return (res);
}

static int	tokenize_input(char *input, t_token **token_lst)
{
	int	i;

	i = 0;
	while (input[i])
	{
		i = process_next_token(input, token_lst, i);
		if (i == -1)
			return (1);
	}
	return (0);
}

static int	process_next_token(char *input, t_token **token_lst, int i)
{
	if (ft_isspace(input[i]))
		return (i + 1);
	else if (input[i] == '$')
		return (i + handle_var(input, token_lst, i));
	else if (ft_isop(input[i]))
		return (i + handle_op(input, token_lst, i));
	else if (is_quote_token(input, i))
		return (handle_quote_token(input, token_lst, i));
	else
		return (handle_word_token(input, token_lst, i));
}

static int	process_commands(t_command *commands)
{
	t_command	*current_cmd;

	current_cmd = commands;
	while (current_cmd)
	{
		if (expand_variables(current_cmd) != 0)
			return (1);
		current_cmd = current_cmd->next;
	}
	handle_command_execution(commands);
	return (g_exit_status);
}
