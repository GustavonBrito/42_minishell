/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:39:52 by luiza             #+#    #+#             */
/*   Updated: 2025/08/03 22:40:33 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//NORMINETTE: too many fts in file. reorder with new file

int		allocate_command_arrays(t_command *cmd, int arg_count);
int		fill_cmd_data(t_command *cmd, t_token **current, int arg_count);
void	free_commands(t_command *cmd);
void	free_redirections(t_redir *redirs);
int		is_argument_token(t_token_type type);
int		is_redirection_token(t_token_type type);
int		handle_redirection_parsing(t_command *cmd, t_token **current);
void	finalize_command_arrays(t_command *cmd, int arg_count);
void	add_redirection(t_command *cmd, t_token_type type, char *file);

/**
 * @brief Aloca os arrays internos de uma estrutura de comando.
 *
 * Esta função aloca memória para os arrays `args`, `quote_removed` e
 * `token_types` dentro da estrutura `t_command`, com base na contagem
 * de argumentos fornecida. Inicializa todos os elementos de `args` como NULL
 * e `quote_removed`/`token_types` com valores padrão.
 *
 * @param cmd Um ptr para a estrutura `t_command` cujos arrays serão alocados.
 * @param arg_count O número de argumentos que o comando terá.
 * @return 1 em caso de sucesso na alocação, 0 em caso de falha.
 */
int	allocate_command_arrays(t_command *cmd, int arg_count)
{
	t_env	*env;
	int count_env;
	int	i;

	count_env = -1;
	env = *handle_t_env(NULL);
	while(env)
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

/**
 * @brief Preenche a estrutura de comando com dados dos tokens.
 *
 * Esta ft itera sobre os tokens e preenche os arrays `args`, `quote_removed`
 * e `token_types` do `t_command`. Ela tb lida com tokens de redirecionamento,
 * chamando `handle_redirection_parsing` para adicioná-los à lista de redirs.
 * Avança o ponteiro de token conforme processa.
 *
 * @param cmd Um ponteiro para a estrutura `t_command` a ser preenchida.
 * @param current Um ponteiro para um ponteiro para o token atual,
 *                permitindo avançar na lista de tokens.
 * @param arg_count O número total de argumentos esperados para o comando.
 * @return 1 em caso de sucesso no preenchimento e tratamento de redirs,
 *         0 em caso de erro de sintaxe ou alocação durante o
 *           tratamento de redirs.
 */
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

/**
 * @brief Libera a memória de uma lista encadeada de estruturas de comando.
 *
 * Esta função percorre uma lista de `t_command` e libera toda a memória
 * associada a cada comando, incluindo seus argumentos, arrays auxiliares
 * e as estruturas de redirecionamento.
 *
 * @param cmd O primeiro ponteiro para a lista de `t_command` a ser liberada.
 */
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

/**
 * @brief Libera a memória de uma lista encadeada de redirecionamentos.
 *
 * Esta função percorre uma lista de `t_redir` e libera toda a memória
 * associada a cada redirecionamento, incluindo o nome do arquivo e a
 * própria estrutura.
 *
 * @param redirs O primeiro ponteiro para a lista de `t_redir` a ser liberada.
 */
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

/**
 * @brief Verifica se um tipo de token representa um argumento de comando.
 *
 * @param type O tipo de token a ser verificado.
 * @return 1 se o token for um WORD, VAR, SINGLE_QUOTE ou DOUBLE_QUOTE,
 *         0 caso contrário.
 */
int	is_argument_token(t_token_type type)
{
	return (type == WORD || type == VAR || type == SINGLE_QUOTE
		|| type == DOUBLE_QUOTE);
}

/**
 * @brief Verifica se um tipo de token representa uma operação de redir.
 *
 * @param type O tipo de token a ser verificado.
 * @return 1 se o token for REDIR_IN, REDIR_OUT, REDIR_APPEND ou HEREDOC,
 *         0 caso contrário.
 */
int	is_redirection_token(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_APPEND || type == HEREDOC);
}

/**
 * @brief Lida com a análise sintática de redirecionamentos.
 *
 * Esta função é chamada quando um token de redirecionamento é encontrado.
 * Ela verifica se há um token de arquivo válido após o redirecionamento
 * e adiciona a informação do redirecionamento à lista `redirs` do comando.
 * Reporta erros de sintaxe se o token de arquivo faltar ou for inválido.
 *
 * @param cmd Um ptr para a  strct `t_command` onde o redir será adicionado.
 * @param current Um ptr para um ptr para o token atual, permitindo avançar
 *                além do token de redirecionamento e do token do arquivo.
 * @return 1 em caso de sucesso na análise e adição do redirecionamento,
 *         0 em caso de erro de sintaxe.
 */
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

/**
 * @brief Finaliza os arrays de argumentos de um comando.
 *
 * Esta função garante que os arrays `args`, `quote_removed` e `token_types`
 * de 1 struct `t_command` sejam devidamente terminados com NULL (para `args`)
 * ou valores padrão (para os outros) na posição `arg_count`.
 *
 * @param cmd Um ponteiro para a struct `t_command` a ser finalizada.
 * @param arg_count O número total de argumentos que o comando possui.
 */
void	finalize_command_arrays(t_command *cmd, int arg_count)
{
	cmd->args[arg_count] = NULL;
	cmd->quote_removed[arg_count] = 0;
	cmd->token_types[arg_count] = WORD;
}

/**
 * @brief Adiciona um novo redir à lista de redirecionamentos de um comando.
 *
 * Esta função aloca uma nova estrutura `t_redir`, copia o nome do arquivo
 * e o tipo de redirecionamento, e a adiciona ao final da lista encadeada
 * de redirecionamentos do comando.
 *
 * @param cmd Um ptr para a struct `t_command` à qual o redir será adicionado.
 * @param type O tipo de redirecionamento (e.g., REDIR_IN, REDIR_OUT).
 * @param file A string contendo o nome do arquivo para o redirecionamento.
 */
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
