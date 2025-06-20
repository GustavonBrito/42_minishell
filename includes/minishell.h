/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:41:22 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/20 00:59:45 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <termcap.h>
# include "../libft/headers/libft.h"
# include "../libft/headers/get_next_line.h"
# include "../libft/headers/ft_printf.h"

typedef enum e_token_type
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

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	char				**args;
	int					*quote_removed;
	t_token_type		*token_types;
	t_redir				*redirs;
	struct s_command	*next;
}	t_command;

//core
extern int	g_exit_status;
void		shell_loop(void);
void		check_exit_condition(char *buffer_received);
void		signal_handler(int signal);

//buitins
void		is_builtin(char **builtin);//Verifica qual builtin foi passado como argumento
void		echo(char **argv); // Funcao para implementar a funcao echo
void		verify_flag(char *argv_splited, int *flag);// Verifica se a flag é valida
void		printf_without_n(char **buffer);// Funcao para printar echo quando tem flag
void		cd(char **argv); // Funcao para alterar o diretorio.
void		env(int is_export);
void		exit_minishell(void);
void		export(char **argv);
void		pwd(void);
void		unset(char **argv);

//lexing
int			process_input(char *input);
int			ft_isspace(char c);
int			ft_isop(char c);
void		add_token(t_token **head, char *input, t_token_type type);
void		free_tokens(t_token *head);

//lex handlers
int			handle_quotes(char *input, t_token **token_lst, int i);
int			handle_var(char *input, t_token **token_lst, int i);

//parsing
t_command	*parse_tokens(t_token *tokens);
int			allocate_command_arrays(t_command *cmd, int arg_count);
int			fill_command_data(t_command *cmd, t_token **current, int arg_count);
void		free_commands(t_command *cmd);
void		free_redirections(t_redir *redirs);
int			is_argument_token(t_token_type type);
int			is_redirection_token(t_token_type type);
int			handle_redirection_parsing(t_command *cmd, t_token **current);
void		finalize_command_arrays(t_command *cmd, int arg_count);
void		add_redirection(t_command *cmd, t_token_type type, char *file);

//expand vars
int			expand_variables(t_command *cmd);
int			expand_exit_status(char **res);
int			expand_process_id(char **res);
int			expand_env_var(const char *str, char **res, int i_cmd);
char		*itoa_exit_status(void);
char		*itoa_process_id(void);
char		*append_str(char *dest, const char *src);
char		*get_env_val(const char *var_name);
char		*append_char(char *dest, char c);
int			handle_dollar_expansion(const char *str, char **res, int i_cmd);
int			handle_regular_char(const char *str, char **res, int i);

//redirs
int			setup_redirections(t_command *cmd);
int			handle_input_redirection(t_redir *redir);
int			handle_output_redirection(t_redir *redir);
int			handle_append_redirection(t_redir *redir);
int			handle_heredoc(t_redir *redir);
int			create_heredoc_file(char *delimiter);
void		restore_std_fds(int saved_stdin, int saved_stdout);

//exec
int			execute_command(t_command *cmd);
int			execute_builtin_with_redirections(t_command *cmd);
int			execute_external_command(t_command *cmd);
void		handle_command_execution(t_command *cmd);
void		handle_command_execution(t_command *cmd);
int			is_builtin_command(char *cmd);

//error handling
int			report_error(const char *msg, int exit_code);
void		critical_error(const char *msg, int exit_code);

// debugs
//void	print_tokens(t_token *head);
//void	print_commands(t_command *cmd);
//void	print_varsexp(t_command *cmd);
//void	print_exit_status(void);

#endif
