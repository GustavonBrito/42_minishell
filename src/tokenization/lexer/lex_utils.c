/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:21:55 by luiza             #+#    #+#             */
/*   Updated: 2025/08/03 22:50:57 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_isspace(char c);
int		ft_isop(char c);
void	add_token(t_token **head, char *input, t_token_type type);
int		handle_escape(char *input, t_token **token_lst);
void	free_tokens(t_token *head);
int		handle_escape(char *input, t_token **token_lst);

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
		return (1);
	else
		return (0);
}

int	ft_isop(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}

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
	char	*w_esc;
	int		j;
	int		a;
	int		final_escape_i;
	int		first_escape_i;
	int		flag;
	size_t	size;
	char	*new_word;

	j = -1;
	first_escape_i = 0;
	flag = 0;
	while (input[++j])
	{
		if (ft_isspace(input[j]) && (ft_isalnum(input[j + 1])
				|| (unsigned char)input[j + 1] > 127) && flag == 0)
		{
			j++;
			flag = 1;
			first_escape_i = j;
		}
	}
	final_escape_i = j;
	w_esc = ft_substr(input, first_escape_i, first_escape_i - final_escape_i);
	size = ft_strlen(w_esc);
	new_word = malloc(sizeof(char) * (size + 1));
	j = -1;
	a = 0;
	while (w_esc[++j])
	{
		if (w_esc[j] != '\\' && w_esc[j] != '/')
		{
			new_word[a] = w_esc[j];
			a++;
		}
	}
	new_word[a] = '\0';
	add_token(token_lst, new_word, DOUBLE_QUOTE);
	free(w_esc);
	free(new_word);
	return (0);
}

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
