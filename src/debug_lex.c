
#include "../includes/minishell.h"
#include <stdio.h>

void	print_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		ft_printf("Token: %s\n", current->value);
		current = current->next;
	}
}
