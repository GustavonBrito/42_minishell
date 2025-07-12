/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:41:22 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/11 21:45:14 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//NORMINETTE: REVIEW ALL FILES AND
//				REMOVE ALL COMMENTS B4 SUBMIT
//				IF BRIEFS PERSISTS NEED TO BE TRANSLATED

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

/**
 * @brief Enumeração dos tipos de tokens reconhecidos no shell.
 *
 * Define os tipos de elementos sintáticos que podem ser encontrados
 * durante a análise léxica da linha de comando.
 */

typedef enum e_token_type
{
	WORD,			/**< Palavra normal (comando ou argumento). */
	PIPE,			/**< Pipe '|'. */
	REDIR_IN,		/**< Redirecionamento de entrada '<'. */
	REDIR_OUT,		/**< Redirecionamento de saída '>'. */
	REDIR_APPEND,	/**< Redirecionamento de append '>>'. */
	HEREDOC,		/**< Redirecionamento heredoc '<<'. */
	SINGLE_QUOTE,	/**< Aspa simples '\''. */
	DOUBLE_QUOTE,	/**< Aspa dupla '"'. */
	VAR,			/**< Variável de ambiente '$VAR'. */
	ESCAPE			/**< Caractere de escape '\\'. */
}	t_token_type;

/**
 * @brief Estrutura que representa um token da linha de comando.
 *
 * Cada token contém um valor em string, seu tipo, e um ponteiro para o
 * próximo token, formando uma lista ligada.
 */

typedef struct s_token
{
	char			*value;	/**< Valor textual do token. */
	t_token_type	type;	/**< Tipo do token (palavra, pipe, redir etc). */
	struct s_token	*next;	/**< Ponteiro para o próximo token na lista. */
}	t_token;

/**
 * @brief Estrutura que representa uma redireção de entrada ou saída.
 *
 * Contém o tipo da redireção, o nome do arquivo associado, e um ponteiro
 * para a próxima redireção, formando uma lista ligada.
 */

typedef struct s_redir
{
	t_token_type	type;	/**< Tipo de redireção (>, >>, < ou <<). */
	char			*file;	/**< Nome do arquivo associado à redireção. */
	struct s_redir	*next;	/**< Ponteiro para a próxima redireção. */
}	t_redir;

/**
 * @brief Estrutura que representa um comando completo.
 *
 * Contém os argumentos do comando, informações sobre as aspas removidas,
 * tipos de tokens, redireções associadas e ponteiro para o próximo comando
 * em caso de pipes.
 */

typedef struct s_command
{
	char				**args;			/**< Array de argumentos do comando. */
	int					*quote_removed;	/**< Flags indicando remoção de aspas. */
	t_token_type		*token_types;	/**< Tipos de tokens associados aos args. */
	t_redir				*redirs;		/**< Lista ligada de redireções. */
	struct s_command	*next;			/**< Próximo comando (pipe). */
}	t_command;

/**
 * @brief Estrutura para controle de pipeline
 *
 * usada para gerenciar os pipes e o controle
 * de execução entre múltiplos comandos encadeados via pipe no shell.
 * Guarda FDs de leitura/escrita dos pipes e índices de controle.
 */
typedef struct s_pipe {
    int     prev_pipe_read;     /* FD de leitura do pipe anterior */
    int     curr_pipe[2];       /* Pipe atual [read, write] */
    int     cmd_index;          /* Índice do comando atual */
    int     total_commands;     /* Total de comandos no pipeline */
} t_pipe;

typedef struct s_env
{
	char			*env_data;			/**< Array de varaveis de ambiente. */
	struct s_env	*next;			/**< Próximo nó. */
}	t_env;

//utils "global" struct
t_env	**handle_t_env(t_env *head);

//core
extern int	g_exit_status;
void		shell_loop(void);
void		check_exit_condition(char *buffer_received);
void		signal_handler(int signal);
char		*obtain_current_directory(void);
char		*get_env_or_cleanup(const char *var, char *to_free);

//paths
void		update_pwd(void);
char		*find_command_path(char *command);
void		free_array(char **path_dirs);

//buitins
void		is_builtin(t_command *cmd);//Verifica qual builtin foi passado como argumento
void		echo(t_command *cmd); // Funcao para implementar a funcao echo
int			verify_flag(char *arg);// Verifica se a flag é valida
void		cd(t_command *cmd); // Funcao para alterar o diretorio.
void		env(int is_export);
void		handle_store_env(char **system_env);
int			handle_escape(char *input, t_token **token_lst);
void		exit_minishell(void);
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
int			handle_tilde_expansion(const char *str, char **res, int i_cmd);
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
int			execute_builtin(t_command *cmd);
int			execute_external_command(t_command *cmd);
void		handle_command_execution(t_command *cmd);
void		handle_command_execution(t_command *cmd);
int			check_builtin(t_command *cmd);

//pipes
int			has_pipes(t_command *cmd);
int			execute_pipeline(t_command *cmd);
void		init_pipeline(t_pipe *pipes, t_command *cmd);
int			count_commands(t_command *cmd);
int			create_pipe(t_pipe *pipes);
void		close_child(t_pipe *pipes);
void		setup_child_pipes(t_pipe *pipes);
void		update_pipes(t_pipe *pipes, t_command *current);
void		execute_child_command(t_command *cmd);

//error handling
int			report_error(const char *msg, int exit_code);
void		critical_error(const char *msg, int exit_code);

// debugs
//void	print_tokens(t_token *head);
//void	print_commands(t_command *cmd);
//void	print_varsexp(t_command *cmd);
//void	print_exit_status(void);

#endif
