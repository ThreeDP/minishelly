/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:14:22 by dapaulin          #+#    #+#             */
/*   Updated: 2023/03/28 11:18:55 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Responsável por contar quantas variaveis
estão declaradas em env */
int	amount_vars(char **envp)
{
	int	len;

	len = 0;
	while (*envp != NULL && envp[len])
		len++;
	return (len);
}

/* Responsável por descobrir o tamanho de caracteres
das keys das variaveis de env */
size_t	keylen(char *var_env)
{
	char	*p;

	p = NULL;
	p = ft_strchr(var_env, '=');
	if (!p)
		return (0);
	return (p - var_env);
}

/* Está função e responsavel por realizar
todos os free na struct */
void	clean_env(char **new_envp)
{
	int	i;

	i = 0;
	while (new_envp[i])
	{
		if (new_envp[i])
			free(new_envp[i]);
		i++;
	}
	if (new_envp)
		free(new_envp);
}

/* Está função é reponsavel por realizar os
allocs de env*/
char	**alloc_env(char **env, int slots)
{
	int		amount;
	char	**new_env;

	amount = amount_vars(env);
	new_env = (char **) ft_calloc(sizeof(char *), amount + slots);
	if (!new_env)
		return (NULL);
	return (new_env);
}

/* valida se env está vazia e alloca um espaço
e insere valor se sim. */
int	env_empty(t_sys_config *mini, char *key, char *value)
{
	if (!mini->env)
	{
		mini->env = (char **) ft_calloc(sizeof(char *), 2);
		mini->env[0] = join_key_value(key, value);
		return (1);
	}
	return (0);
}
