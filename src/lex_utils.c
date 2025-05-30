/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:21:55 by luiza             #+#    #+#             */
/*   Updated: 2025/05/30 03:13:09 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_isspace(char c);
int		ft_isop(char c);
void	add_token(t_token **head, char *input, t_token_type type);
void	free_tokens(t_token *head);

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
	if(!new->value)
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
