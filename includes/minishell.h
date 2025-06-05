/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:41:22 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/05 01:44:43 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "../libft/headers/libft.h"
#include "../libft/headers/get_next_line.h"
#include "../libft/headers/ft_printf.h"

typedef enum	e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	VAR
}	t_token_type;

typedef struct	s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct	s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct	s_command
{
	char				**args;
	t_redir				*redirs;
	struct s_command	*next;
}	t_command;


void	shell_loop(void);
void	check_exit_condition(char *buffer_received);
void	signal_handler(int signal);

//lexing
void	process_input(char *input);
int		ft_isspace(char c);
int		ft_isop(char c);
void	add_token(t_token **head, char *input, t_token_type type);
void	free_tokens(t_token *head);

//lex handlers
int	handle_quotes(char *input, t_token **token_lst, int i);
int	handle_var(char *input, t_token **token_lst, int i);

//parsing
t_command	*parse_tokens(t_token *tokens);
void		free_commands(t_command *cmd);
void		print_commands(t_command *cmd);

// debugs
void	print_tokens(t_token *head);
void	print_commands(t_command *cmd);

#endif
