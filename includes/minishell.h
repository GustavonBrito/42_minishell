/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:41:22 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/29 18:34:38 by luiza            ###   ########.fr       */
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
# include <errno.h>
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
	VAR,
	ESCAPE
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

typedef struct s_pipe
{
	int		**pipe_fds;
	pid_t	*pids;
	int		total_commands;
}	t_pipe;

typedef struct s_env
{
	char			*env_data;
	struct s_env	*next;
}	t_env;

//core
extern int	g_exit_status;
void		shell_loop(void);
void		check_exit_condition(char *buffer_received);
void		signal_handler(int signal);
char		*obtain_current_directory(void);
char		*get_env_or_cleanup(const char *var, char *to_free);
t_env		**handle_t_env(t_env *head);

//paths
void		update_pwd(void);
char		*find_command_path(char *command);
void		free_array(char **path_dirs);

//buitins
void		is_builtin(t_command *cmd);
void		echo(t_command *cmd);
int			verify_flag(char *arg);
void		cd(t_command *cmd);
void		env(int is_export);
void		handle_store_env(char **system_env);
int			handle_escape(char *input, t_token **token_lst);
void		exit_minishell(t_command *cmd);
void		export(t_command *cmd);
void		pwd(void);
void		unset(t_command *cmd);
void		ft_free_split(char **array);
int			verify_remove_env(char **argv, t_env *s_env);

//lexing
int			process_input(char *input);
int			ft_isspace(char c);
int			ft_isop(char c);
void		add_token(t_token **head, char *input, t_token_type type);
void		free_tokens(t_token *head);

//lex handlers
int			handle_quotes(char *input, t_token **token_lst, int i);
int			handle_var(char *input, t_token **token_lst, int i);
int			handle_attribution_w_quote(char *input, t_token **token_lst, int i);
int			handle_escape(char *input, t_token **token_lst);
int			handle_word_with_quotes(char *input, t_token **token_lst, int i);

//parsing
t_command	*parse_tokens(t_token *tokens);
t_command	*init_command(void);
int			allocate_command_arrays(t_command *cmd, int arg_count);
int			fill_command_data(t_command *cmd, t_token **current, int arg_count);
void		free_commands(t_command *cmd);
void		free_redirections(t_redir *redirs);
int			is_argument_token(t_token_type type);
int			is_redirection_token(t_token_type type);
int			handle_redirection_parsing(t_command *cmd, t_token **current);
void		finalize_command_arrays(t_command *cmd, int arg_count);
void		add_redirection(t_command *cmd, t_token_type type, char *file);
t_command	*init_command(void);

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
int			handle_tilde_expansion(const char *str, char **res, int i_cmd);
int			handle_regular_char(const char *str, char **res, int i);
char		*remove_quotes(char *str);

//redirs
int			setup_redirections(t_command *cmd);
int			handle_input_redirection(t_redir *redir);
int			handle_output_redirection(t_redir *redir);
int			handle_append_redirection(t_redir *redir);
int			handle_heredoc(t_redir *redir);
int			create_heredoc_file(char *delimiter);
void		restore_std_fds(int saved_stdin, int saved_stdout);
int			validate_redirection(t_redir *redir);
int			apply_redirection(t_redir *redir);

//exec
int			execute_command(t_command *cmd);
int			execute_builtin(t_command *cmd);
int			execute_external_command(t_command *cmd);
void		handle_command_execution(t_command *cmd);
int			check_builtin(t_command *cmd);
int			execute_with_execve(t_command *cmd);

//pipes
int			has_pipes(t_command *cmd);
int			execute_pipeline(t_command *cmd);
int			init_pipeline(t_pipe *pipes, t_command *cmd);
int			count_commands(t_command *cmd);
int			create_pipe(int pipe_fd[2]);
void		cleanup_pipeline(t_pipe *pipes);
void		setup_child_pipes(t_pipe *pipes, int cmd_index);
void		execute_child_command(t_command *cmd);

//error handling
int			report_error(const char *msg, int exit_code);
void		critical_error(const char *msg, int exit_code);
void		write_err(const char *msg);

#endif
