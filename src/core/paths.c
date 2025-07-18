/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:59:26 by luiza             #+#    #+#             */
/*   Updated: 2025/07/18 00:03:26 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FILE HAS NORMINETTE ERRORS -> NOTES B4 FTS WITH ERRORS

void	update_pwd(void);
char	*find_command_path(char *command);
void	free_array(char **path_dirs);

/**
 * @brief Atualiza a variável de ambiente PWD.
 *
 * Obtém o diretório de trabalho atual via getcwd e atualiza a variável
 * de ambiente PWD com esse valor usando setenv. Libera a memória alocada
 * após a atualização.
 */

void	update_pwd(void)
{
	t_command	*cmd;
	char		*new_dir;
	char		*actual_directory;

	actual_directory = getcwd(NULL, 0);
	if (!actual_directory)
		return ;
	cmd = init_command();
	if (!cmd || !allocate_command_arrays(cmd, 1))
	{
		free(actual_directory);
		if (cmd)
			free(cmd);
		return ;
	}
	new_dir = ft_strjoin("PWD=",actual_directory);
	if (!new_dir)
	{
		free(actual_directory);
		free_commands(cmd);
		return ;
	}
	cmd->args[1] = ft_strdup(new_dir);
	if (cmd->args[1])
		export(cmd);
	free(actual_directory);
	free(new_dir);
	free_commands(cmd);
}

/**
 * @brief Encontra o caminho completo de um comando usando a variável PATH.
 *
 * Esta função procura por um comando executável nos diretórios listados
 * na variável de ambiente PATH.
 *
 * @param command O nome do comando a ser procurado.
 * @return O caminho completo do comando se encontrado, ou NULL caso contrário.
 *         O ponteiro retornado deve ser liberado com free().
 */

//norminette: +25 lines: needs to be chopped
char	*find_command_path(char *command)
{
	char	*path_env;
	char	**path_dirs;
	char	*full_path;
	char	*temp_path;
	int		i;

	if (!command)
		return (NULL);
	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
		return (NULL);
	i = -1;
	while (path_dirs[++i])
	{
		temp_path = ft_strjoin(path_dirs[i], "/");
		full_path = ft_strjoin(temp_path, command);
		free(temp_path);
		if (access(full_path, X_OK) == 0)
		{
			free_array(path_dirs);
			return (full_path);
		}
		free(full_path);
	}
	free_array(path_dirs);
	return (NULL);
}

/**
 * @brief Libera um array de strings e o array principal.
 *
 * Percorre o array de strings e libera cada elemento individualmente,
 * depois libera o próprio array.
 *
 * @param path_dirs O array de strings a ser liberado.
 */

void	free_array(char **path_dirs)
{
	int	i;

	i = -1;
	while (path_dirs[++i])
		free(path_dirs[i]);
	free(path_dirs);
}
