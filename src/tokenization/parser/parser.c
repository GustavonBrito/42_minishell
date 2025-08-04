/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:35:32 by luiza             #+#    #+#             */
/*   Updated: 2025/08/03 22:46:15 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command			*parse_tokens(t_token *tokens);
static t_command	*parse_command(t_token **current);
t_command			*init_command(void);
static int			count_args(t_token *start);

t_command	*parse_tokens(t_token *tokens)
{
	t_command	*first_command;
	t_command	*current_command;
	t_token		*current_token;

	if (!tokens)
		return (NULL);
	current_token = tokens;
	first_command = parse_command(&current_token);
	if (!first_command)
		return (NULL);
	current_command = first_command;
	while (current_token && current_token->type == PIPE)
	{
		current_token = current_token->next;
		if (!current_token)
		{
			report_error("syntax error near unexpected token 'newline'", 2);
			free_commands(first_command);
			return (NULL);
		}
		current_command->next = parse_command(&current_token);
		if (!current_command->next)
		{
			free_commands(first_command);
			return (NULL);
		}
		current_command = current_command->next;
	}
	return (first_command);
}

static t_command	*parse_command(t_token **current)
{
	t_command	*cmd;
	int			arg_count;

	cmd = init_command();
	if (!cmd)
		return (NULL);
	arg_count = count_args(*current);
	if (!allocate_command_arrays(cmd, arg_count))
	{
		free_commands(cmd);
		return (NULL);
	}
	if (!fill_cmd_data(cmd, current, arg_count))
	{
		free_commands(cmd);
		return (NULL);
	}
	return (cmd);
}

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->quote_removed = NULL;
	cmd->token_types = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

static int	count_args(t_token *start)
{
	int	count;

	count = 0;
	while (start && start->type != PIPE)
	{
		if (start->type == WORD || start->type == VAR
			|| start->type == SINGLE_QUOTE || start->type == DOUBLE_QUOTE)
			count++;
		else if (start->type == REDIR_IN || start->type == REDIR_OUT
			|| start->type == REDIR_APPEND || start->type == HEREDOC)
		{
			start = start->next;
			if (start)
				start = start->next;
			continue ;
		}
		start = start->next;
	}
	return (count);
}
