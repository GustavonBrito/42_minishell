/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:21:55 by luiza             #+#    #+#             */
/*   Updated: 2025/06/24 00:28:15 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_isspace(char c);
int		ft_isop(char c);
void	add_token(t_token **head, char *input, t_token_type type);
int		handle_escape(char *input, t_token **token_lst, int i);
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

int		handle_escape(char *input, t_token **token_lst, int i)
{
	char	*word_escaped;
	int j;
	int actual_final_len;
	int actual_init_len;
	t_token_type	token;

	j = -1;
	actual_final_len = 0;
	actual_init_len = 0;
	while (input[++j])
	{
		if (ft_isspace(input[j]) && ft_isalnum(input[j + 1]))
		{
			j++;
			actual_init_len = j;
		}
		if (input[j] == '\\' && ft_isspace(input[j + 1]))
		{
			actual_final_len = j;
		}
	}
	word_escaped = ft_substr(input,actual_init_len, actual_final_len);
	add_token(token_lst, word_escaped, ESCAPE);
}//Tem que implementar a logica apos pegar o indice comeco e o indice final depois de '\'

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
