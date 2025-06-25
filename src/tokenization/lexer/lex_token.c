/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:21:55 by luiza             #+#    #+#             */
/*   Updated: 2025/06/24 23:30:24 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FILE HAS NORMINETTE ERRORS -> NOTES B4 FTS WITH ERRORS
//NORMINETTE: too many fts in file. reorder with new file

int			process_input(char *input);
static int	lex_token(char *input);
static int	tokenize_input(char *input, t_token **token_lst);
static int	process_commands(t_command *commands);
static int	handle_op(char *input, t_token **token_lst, int i);
static int	handle_word(char *input, t_token **token_lst, int i);
int			handle_attribution_w_quote(char *input, t_token **token_lst, int i);
int			is_assignment_with_quotes(char *input, int start);

/**
 * @brief Ponto de entrada principal para processar uma linha de entrada.
 *
 * Verifica se a entrada é nula ou vazia. Se for válida, inicia o processo de
 * tokenização, parsing e execução do comando.
 *
 * @param input A linha de entrada recebida do readline.
 * @return 0 se a entrada for vazia, ou o status de saída do último comando
 *         processado (ou 1 em caso de erro de sintaxe/alocação durante
 *         o processamento).
 */
int	process_input(char *input)
{
	if (!input || ft_strlen(input) == 0)
		return (0);
	return (lex_token(input));
}

/**
 * @brief Orquestra etapas de tokenização, parsing e processamento de comandos.
 *
 * Cria uma lista de tokens a partir da entrada, então analisa esses tokens
 * para formar uma lista de comandos. Finalmente, processa (executa) comandos.
 * Gerencia a liberação de memória para tokens e comandos.
 *
 * @param input A linha de entrada a ser processada.
 * @return O status de saída do comando processado, ou 1 em caso de erro.
 */
static int	lex_token(char *input)
{
	t_token		*token_lst;
	t_command	*commands;
	int			res;

	token_lst = NULL;
	res = tokenize_input(input, &token_lst);
	if (res != 0)
		return (res);
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

/**
 * @brief Tokeniza a string de entrada em uma lista de tokens.
 *
 * Percorre a string de entrada, identificando diferentes tipos de elementos
 * como espaços, aspas (simples/duplas), variáveis, operadores, escapes
 * e palavras.
 * Para cada elemento, chama a função `handle_*` apropriada para criar e
 * adicionar um token à lista.
 *
 * @param input A string de entrada a ser tokenizada.
 * @param token_lst Um ponteiro para a lista de tokens (será preenchida).
 * @return 0 em caso de sucesso na tokenização, ou 1 em caso de erro
 *         (e.g., aspas não fechadas).
 */

//norminette:+25 lines needs to be chopped
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
		/* else if (input[i] == '\\')
			i += handle_escape(input, token_lst, i); */
		else
		{
			if (is_assignment_with_quotes(input, i))
				i += handle_attribution_w_quote(input, token_lst, i);
			else
				i += handle_word(input, token_lst, i);
		}
	}
	return (0);
}

/**
 * @brief Processa e executa uma lista de comandos.
 *
 * Esta função itera sobre uma lista encadeada de comandos (`t_command`).
 * Para cada comando, ela realiza a expansão de variáveis e, em seguida,
 * chama a função de execução de comando apropriada.
 *
 * @param commands O primeiro ptr para a lista de `t_command` a ser processada.
 * @return 0 em caso de sucesso, ou 1 se houver erro durante a exp de vars.
 */

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
	//print_varsexp(commands);
	handle_command_execution(commands);
	return (0);
}

/**
 * @brief Lida com a tokenização de operadores.
 *
 * Esta função verifica se o caractere atual é um operador (`|`, `<`, `>`).
 * Ela também lida com operadores de dois caracteres como `<<` (heredoc) e
 * `>>` (redirecionamento de append). Adiciona o token apropriado à lista.
 *
 * @param input A string de entrada completa.
 * @param token_lst Um ponteiro para a lista de tokens.
 * @param i O índice atual na string de entrada onde o operador foi encontrado.
 * @return O número de caracteres do operador processados (1 ou 2).
 */

//norminette:+25 lines needs to be chopped
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

/**
 * @brief Lida com a tokenização de palavras comuns.
 *
 * Esta função extrai uma "palavra" da string de entrada. Uma palavra
 * é definida como uma sequência de caracteres que não são espaços, operadores,
 * aspas ou o caractere '$'. A palavra extraída é adicionada à lista de tokens
 * como um token `WORD`.
 *
 * @param input A string de entrada completa.
 * @param token_lst Um ponteiro para a lista de tokens.
 * @param i O índice atual na string de entrada onde a palavra começa.
 * @return O comprimento da palavra processada.
 */
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

//norminette:+25 lines needs to be chopped
int	handle_attribution_w_quote(char *input, t_token **token_lst, int i)
{
	int		start;
	int		j;
	char	*full_word;
	int		len;
	char	quote_char;

	start = i;
	j = i;
	while (input[j] && !ft_isspace(input[j]) && !ft_isop(input[j])
		&& input[j] != '$')
	{
		if (input[j] == '\'' || input[j] == '"')
		{
			quote_char = input[j];
			j++;
			while (input[j] && input[j] != quote_char)
				j++;
			if (input[j] == quote_char)
				j++;
		}
		else
			j++;
	}
	len = j - start;
	full_word = ft_substr(input, start, len);
	if (!full_word)
		return (len);
	add_token(token_lst, full_word, WORD);
	free(full_word);
	return (len);
}

int	is_assignment_with_quotes(char *input, int start)
{
	int	i;

	i = start;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		i++;
	if (input[i] == '=' && (input[i + 1] == '"' || input[i + 1] == '\''))
		return (1);
	return (0);
}
