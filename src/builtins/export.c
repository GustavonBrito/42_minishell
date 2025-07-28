/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:28 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/28 00:29:07 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FILE HAS NORMINETTE ERRORS -> NOTES B4 FTS WITH ERRORS

void	export(t_command *cmd);
char	*ft_strjoin_free(char *s1, char *s2);

/**
 * @brief Implementa o comando 'export'.
 *
 * Esta função manipula variáveis de ambiente.
 * Se chamada sem argumentos, comporta-se como `env` com o modo de exportação,
 * retornando env(1), ou seja, exibindo todas as vars de ambiente formatadas
 * com "declare -x".
 * Se argumentos forem fornecidos, verifica se cada argumento é do tipo
 * WORD (definido pela tokenização em `cmd->token_types`) e se contém um '=',
 * criando ou atualizando a variável de ambiente correspondente e
 * removendo aspas se necessário.
 *
 * @param cmd Estrutura contendo os argumentos e informações do comando.
 */

//norminette:+25 lines needs to be chopped
void	export(t_command *cmd)
{
	int		i;
	int		j;
	int		equal_sign_passed;
	int		first_num_passed;
	char	*equal_sign;
	char	*verify_valid_var;
	t_env	*s_env;
	t_env	*new_var;

	if (!cmd->args[1])
	{
		env(1);
		return ;
	}
	i = 1;
	equal_sign_passed = 0;
	first_num_passed = 0;
	while (cmd->args[i])
	{
		j = 0;
		if (cmd->token_types[i] == WORD)
		{
			equal_sign = ft_strchr(cmd->args[i], '=');
			verify_valid_var = ft_strdup(cmd->args[i]);
			while (verify_valid_var[j] && equal_sign_passed == 0)
			{
				if (ft_isalnum(verify_valid_var[j]) == 4 && first_num_passed == 0)
				{
					write(2, " not a valid identifier", 23);
					exit(1);
				}
				if (verify_valid_var[j] == '=')
					equal_sign_passed = 1;
				if (ft_isalnum(verify_valid_var[j]) == 0 && (verify_valid_var[j] != '=' || verify_valid_var[j + 1] == '\0'))
				{
					write(2, " not a valid identifier", 23);
					exit(1);
				}
				j++;
				first_num_passed = 1;
			}
			if (equal_sign)
			{
				*equal_sign = '\0';
				s_env = *handle_t_env(NULL);
				while (s_env)
				{
					if (ft_strncmp(s_env->env_data, cmd->args[i],
							ft_strlen(cmd->args[i])) == 0
						&& s_env->env_data[ft_strlen(cmd->args[i])] == '=')
					{
						free(s_env->env_data);
						s_env->env_data = ft_strdup(cmd->args[i]); // key
						s_env->env_data = ft_strjoin_free(s_env->env_data, "=");
						s_env->env_data = ft_strjoin_free(s_env->env_data, equal_sign + 1);
						*equal_sign = '=';
						break ;
					}
					if (!s_env->next)
						break ;
					s_env = s_env->next;
				}
				if (!s_env || (s_env && s_env->next == NULL))
				{
					new_var = malloc(sizeof(t_env));
					new_var->env_data = ft_strdup(cmd->args[i]);
					new_var->env_data = ft_strjoin_free(new_var->env_data, "=");
					new_var->env_data = ft_strjoin_free(new_var->env_data, equal_sign + 1);
					new_var->next = NULL;
					if (s_env)
						s_env->next = new_var;
					else
						handle_t_env(new_var);
				}
				*equal_sign = '=';
			}
		}
		i++;
	}
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char *joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}
