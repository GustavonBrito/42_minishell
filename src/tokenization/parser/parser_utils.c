/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:39:52 by luiza             #+#    #+#             */
/*   Updated: 2025/08/05 02:32:04 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		allocate_command_arrays(t_command *cmd, int arg_count);
int		fill_cmd_data(t_command *cmd, t_token **current, int arg_count);
void	free_commands(t_command *cmd);
void	free_redirections(t_redir *redirs);
int		is_argument_token(t_token_type type);
int		is_redirection_token(t_token_type type);
int		handle_redirection_parsing(t_command *cmd, t_token **current);
void	finalize_command_arrays(t_command *cmd, int arg_count);
void	add_redirection(t_command *cmd, t_token_type type, char *file);
int		handle_parse_error(t_token *token, t_command *first_cmd);

int	allocate_command_arrays(t_command *cmd, int arg_count)
{
	t_env	*env;
	int		count_env;
	int		i;

	count_env = -1;
	env = *handle_t_env(NULL);
	while (env)
	{
		env = env->next;
		count_env++;
	}
	cmd->args = malloc(sizeof(char *) * (count_env + 1));
	cmd->quote_removed = malloc(sizeof(int) * (arg_count + 1));
	cmd->token_types = malloc(sizeof(t_token_type) * (arg_count + 1));
	if (!cmd->args || !cmd->quote_removed || !cmd->token_types)
		return (0);
	i = 0;
	while (i <= count_env)
	{
		cmd->args[i] = NULL;
		i++;
	}
	i = 0;
	while (i <= arg_count)
	{
		cmd->quote_removed[i] = 0;
		cmd->token_types[i] = WORD;
		i++;
	}
	return (1);
}

int	fill_cmd_data(t_command *cmd, t_token **current, int arg_count)
{
	int	arg_index;

	arg_index = 0;
	while (*current && (*current)->type != PIPE)
	{
		if (is_argument_token((*current)->type))
		{
			cmd->args[arg_index] = ft_strdup((*current)->value);
			cmd->quote_removed[arg_index] = 1;
			cmd->token_types[arg_index] = (*current)->type;
			arg_index++;
		}
		else if (is_redirection_token((*current)->type))
		{
			if (!handle_redirection_parsing(cmd, current))
				return (0);
		}
		*current = (*current)->next;
	}
	finalize_command_arrays(cmd, arg_count);
	return (1);
}

void	free_commands(t_command *cmd)
{
	t_command	*temp;
	int			i;

	while (cmd)
	{
		temp = cmd->next;
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				free(cmd->args[i]);
				i++;
			}
			free(cmd->args);
		}
		if (cmd->quote_removed)
			free(cmd->quote_removed);
		if (cmd->token_types)
			free(cmd->token_types);
		free_redirections(cmd->redirs);
		free(cmd);
		cmd = temp;
	}
}

void	free_redirections(t_redir *redirs)
{
	t_redir	*temp;

	while (redirs)
	{
		temp = redirs->next;
		free(redirs->file);
		free(redirs);
		redirs = temp;
	}
}

int	is_argument_token(t_token_type type)
{
	return (type == WORD || type == VAR || type == SINGLE_QUOTE
		|| type == DOUBLE_QUOTE);
}

int	is_redirection_token(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_APPEND || type == HEREDOC);
}

int	handle_redirection_parsing(t_command *cmd, t_token **current)
{
	t_token_type	redir_type;
	t_token			*file_token;

	redir_type = (*current)->type;
	*current = (*current)->next;
	if (!*current)
	{
		report_error("syntax error near unexpected token 'newline'", 2);
		return (0);
	}
	file_token = *current;
	if (!is_argument_token(file_token->type))
	{
		report_error("syntax error: expected filename after redirection", 2);
		return (0);
	}
	add_redirection(cmd, redir_type, file_token->value);
	return (1);
}

void	finalize_command_arrays(t_command *cmd, int arg_count)
{
	cmd->args[arg_count] = NULL;
	cmd->quote_removed[arg_count] = 0;
	cmd->token_types[arg_count] = WORD;
}

void	add_redirection(t_command *cmd, t_token_type type, char *file)
{
	t_redir	*new_redir;
	t_redir	*current;
	char	*clean_file;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	clean_file = remove_quotes(file);
	if (!clean_file)
	{
		free(new_redir);
		return ;
	}
	new_redir->file = clean_file;
	new_redir->type = type;
	new_redir->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = new_redir;
	else
	{
		current = cmd->redirs;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}

int	handle_parse_error(t_token *token, t_command *first_cmd)
{
	if (!token)
	{
		report_error("syntax error near unexpected token 'newline'", 2);
		free_commands(first_cmd);
		return (0);
	}
	return (1);
}
