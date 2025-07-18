/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:35:32 by luiza             #+#    #+#             */
/*   Updated: 2025/07/17 23:52:13 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FILE HAS NORMINETTE ERRORS -> NOTES B4 FTS WITH ERRORS

t_command			*parse_tokens(t_token *tokens);
static t_command	*parse_command(t_token **current);
t_command	*init_command(void);
static int			count_args(t_token *start);

/**
 * @brief Analisa uma lista de tokens para construir uma estrutura de comandos.
 *
 * Esta é a função principal do parser. Ela recebe uma lista encadeada de tokens
 * e a processa para criar uma ou mais estruturas `t_command`, representando
 * comandos individuais e pipelines. Lida com erros de sintaxe para pipes.
 *
 * @param tokens Um ponteiro para o primeiro token da lista a ser analisada.
 * @return Um ponteiro para a primeira estrutura `t_command` na lista de comandos
 *         analisados, ou NULL em caso de erro de alocação ou sintaxe.
 */

//norminette:+25 lines needs to be chopped
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

/**
 * @brief Analisa um único comando a partir da lista de tokens.
 *
 * Esta função é responsável por extrair um único comando (incluindo seus
 * argumentos e redirecionamentos) da corrente de tokens. Ela inicializa
 * a estrutura do comando, aloca memória para seus arrays de argumentos
 * e preenche os dados.
 *
 * @param current Um ponteiro para um ponteiro para o token atual,
 *                permitindo que a função avance o ponteiro global de tokens.
 * @return Um ponteiro para a estrutura `t_command` recém-criada e preenchida,
 *         ou NULL em caso de erro.
 */
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
	if (!fill_command_data(cmd, current, arg_count))
	{
		free_commands(cmd);
		return (NULL);
	}
	return (cmd);
}

/**
 * @brief Inicializa e aloca memória para uma nova estrutura de comando.
 *
 * Esta função cria uma nova instância de `t_command` e inicializa seus
 * membros com valores NULL ou zero, preparando-a para ser preenchida
 * com dados de argumentos e redirecionamentos.
 *
 * @return Um ponteiro para a nova estrutura `t_command` alocada,
 *         ou NULL se a alocação de memória falhar.
 */
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

/**
 * @brief Conta o número de argumentos válidos em uma sequência de tokens.
 *
 * Esta função percorre uma lista de tokens a partir de um ponto inicial
 * e conta quantos tokens representam argumentos (palavras, variáveis,
 * strings entre aspas simples ou duplas). Redirecionamentos são pulados,
 * pois não são considerados argumentos para o comando principal. A contagem
 * para quando um PIPE é encontrado ou a lista de tokens termina.
 *
 * @param start Um ponteiro para o token de onde a contagem deve começar.
 * @return O número de argumentos válidos encontrados.
 */
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
