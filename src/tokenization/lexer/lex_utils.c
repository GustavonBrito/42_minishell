/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:21:55 by luiza             #+#    #+#             */
/*   Updated: 2025/07/02 00:44:40 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_isspace(char c);
int		ft_isop(char c);
void	add_token(t_token **head, char *input, t_token_type type);
int		handle_escape(char *input, t_token **token_lst);
void	free_tokens(t_token *head);

/**
 * @brief Verifica se um caractere é um espaço em branco.
 *
 * @param c O caractere a ser verificado.
 * @return 1 se o caractere for ' ', '\t', '\n' ou '\r', 0 caso contrário.
 */
int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
		return (1);
	else
		return (0);
}

/**
 * @brief Verifica se um caractere é um operador de shell.
 *
 * @param c O caractere a ser verificado.
 * @return 1 se o caractere for '|', '<' ou '>', 0 caso contrário.
 */
int	ft_isop(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}

/**
 * @brief Adiciona um novo token ao final de uma lista encadeada de tokens.
 *
 * Aloca memória para um novo `t_token`, duplica o valor da string de entrada,
 * define seu tipo e o anexa ao final da lista `head`.
 *
 * @param head Um ponteiro para o ponteiro para o início da lista de tokens.
 *             Será atualizado se a lista estiver vazia.
 * @param input A string de valor para o novo token.
 * @param type O tipo do novo token (e.g., WORD, PIPE, REDIR_IN).
 */
void	add_token(t_token **head, char *input, t_token_type type)
{
	t_token	*new;
	t_token	*temp;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->value = ft_strdup(input);
	if (!new->value)
	{
		free(new);
		return ;
	}
	new->type = type;
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

int	handle_escape(char *input, t_token **token_lst)
{
	char	*word_escaped;
	int 	j;
	int 	a;
	int		final_escape_index;
	int 	first_escape_index;
	int		flag;
	size_t  size;
	char *new_word;

	j = -1;
	first_escape_index = 0;
	flag = 0;
	while (input[++j])
	{
		if (ft_isspace(input[j]) && (ft_isalnum(input[j + 1]) || (unsigned char)input[j + 1] > 127) && flag == 0)
		{
			j++;
			flag = 1;
			first_escape_index = j;
		}
	}
	final_escape_index = j;
	word_escaped = ft_substr(input, first_escape_index, first_escape_index - final_escape_index);
	size = ft_strlen(word_escaped);
	new_word = malloc(sizeof(char) * (size + 1));
	j = -1;
	a = 0;
	while(word_escaped[++j])
	{
		if (word_escaped[j] != '\\' && word_escaped[j] != '/')
		{
			new_word[a] = word_escaped[j];
			a++;
		}
	}
	new_word[a] = '\0';
	add_token(token_lst, new_word, DOUBLE_QUOTE);
	return (0);
}
/**
 * @brief Libera toda a memória alocada para uma lista encadeada de tokens.
 *
 * Percorre a lista de tokens e libera a string de valor de cada token
 * e a própria estrutura `t_token`.
 *
 * @param head O ponteiro para o início da lista de tokens a ser liberada.
 */

void	free_tokens(t_token *head)
{
	t_token	*temp;

	while (head)
	{
		temp = head->next;
		free(head->value);
		free(head);
		head = temp;
	}
}
