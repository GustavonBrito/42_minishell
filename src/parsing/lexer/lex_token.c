/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:21:55 by luiza             #+#    #+#             */
/*   Updated: 2025/06/11 00:42:20 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			process_input(char *input);
static int	lex_token(char *input);
static int	tokenize_input(char *input, t_token **token_lst);
static int	process_commands(t_command *commands);
static int	handle_op(char *input, t_token **token_lst, int i);
static int	handle_word(char *input, t_token **token_lst, int i);

int	process_input(char *input)
{
	if (!input || ft_strlen(input) == 0)
		return (g_exit_status);
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
		return (res);
	//tester print for debbug
	print_tokens(token_lst);
	commands = parse_tokens(token_lst);
	if (!commands)
	{
		free_tokens(token_lst);
		return (1);
	}
	res = process_commands(commands);
	free_commands(commands);
	free_tokens(token_lst);
	return (res);
}

static int	tokenize_input(char *input, t_token **token_lst)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (input[i] == '\'' || input[i] == '"')
		{
			res = handle_quotes(input, token_lst, i);
			if (res == 1)
			{
				free_tokens(*token_lst);
				return (1);
			}
			i += res;
		}
		else if (input[i] == '$')
			i += handle_var(input, token_lst, i);
		else if (ft_isop(input[i]))
			i += handle_op(input, token_lst, i);
		else
			i += handle_word(input, token_lst, i);
	}
	return (0);
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
	//tester print for debbug
	print_varsexp(commands);
	handle_command_execution(commands);
	return (0);
}

static int	handle_op(char *input, t_token **token_lst, int i)
{
	if (input[i] == '|')
	{
		add_token(token_lst, "|", PIPE);
		return (1);
	}
	else if (input[i] == '<')
	{
		if (input[i + 1] == '<')
		{
			add_token(token_lst, "<<", HEREDOC);
			return (2);
		}
		add_token(token_lst, "<", REDIR_IN);
		return (1);
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == '>')
		{
			add_token(token_lst, ">>", REDIR_APPEND);
			return (2);
		}
		add_token(token_lst, ">", REDIR_OUT);
		return (1);
	}
	return (0);
}

static int	handle_word(char *input, t_token **token_lst, int i)
{
	int		start;
	char	*word;
	int		len;

	start = i;
	while (input[i] && !ft_isspace(input[i]) && !ft_isop(input[i])
			&& input[i] != '\'' && input[i] != '"' && input[i] != '$')
		i++;
	len = i - start;
	word = ft_substr(input, start, len);
	if (!word)
		return (len);
	add_token(token_lst, word, WORD);
	free (word);
	return (len);
}
