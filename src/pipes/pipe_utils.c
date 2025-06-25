/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:55:08 by luiza             #+#    #+#             */
/*   Updated: 2025/06/24 17:58:46 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FILE HAS NORMINETTE ERRORS -> NOTES B4 FTS WITH ERRORS

int		count_commands(t_command *cmd);
int		**create_pipes(int cmd_count);
void	close_all_pipes(int **pipes, int pipe_count);
void	free_pipes(int **pipes, int pipe_count);

/**
 * @brief Conta o número de comandos em uma lista encadeada de `t_command`.
 *
 * Percorre a lista de comandos e retorna a quantidade de elementos.
 *
 * @param cmd Ponteiro para o primeiro comando.
 * @return Número de comandos na lista.
 */

int	count_commands(t_command *cmd)
{
	int			count;
	t_command	*current;

	if (!cmd)
		return (0);
	count = 0;
	current = cmd;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/**
 * @brief Cria os pipes necessários para uma pipeline.
 *
 * Aloca e inicializa os descritores de arquivo de cada pipe.
 * Se ocorrer erro em alguma criação, libera os recursos alocados.
 *
 * @param cmd_count Número total de comandos na pipeline.
 * @return Array bidimensional de descritores de pipes ou NULL em caso de erro.
 */

//norminette:+25 lines needs to be chopped
int	**create_pipes(int cmd_count)
{
	int	**pipes;
	int	i;

	if (cmd_count <= 1)
		return (NULL);
	pipes = malloc(sizeof(int *) * (cmd_count - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < cmd_count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			while (--i >= 0)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
				free(pipes[i]);
			}
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

/**
 * @brief Libera a memória alocada para os pipes.
 *
 * Percorre o array de pipes e libera cada elemento, depois o array principal.
 *
 * @param pipes Array de pipes alocados.
 * @param pipe_count Quantidade de pipes.
 */

void	close_all_pipes(int **pipes, int pipe_count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	free_pipes(int **pipes, int pipe_count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < pipe_count)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}
