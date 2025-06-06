/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:41:22 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/06 15:42:53 by gustavo-lin      ###   ########.fr       */
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


typedef struct s_builtins
{
	char	*name; // nome do builtin
	int		flag;
	void* (*function)(char **args); // ponteiro para a funcao
}	t_builtins;

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


void	shell_loop(void); // Loop principal aonde o minishell roda
void	check_exit_condition(char *buffer_received);  // funcao para checar se exit foi escrito no terminal.
void	signal_handler(int signal); // Lida com os sinais UNIX como ctrl c, ctrl d
void	is_builtin(char *builtin); //Verifica qual builtin foi passado como argumento
void	echo(char *builtin, t_builtins **builtins); // Funcao para implementar a funcao echo
void	verify_flag(char *argv_splited, t_builtins **builtins); // Verifica se a flag é valida
void	printf_without_n(char **buffer); // Funcao para printar echo quando tem flag
void	cd(char *argv, t_builtins **builtins); // Funcao para alterar o diretorio.
void	env(void);
void	exit_minishell(void);
void	export(void);
void	pwd(void);
void	unset(void);

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
void	print_commands(t_command *cmd); // Talvez remover essa funcao, esta duplicada.

#endif
