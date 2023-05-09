/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:12:28 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/09 17:14:24 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit(t_sys_config *mini)
{
	printf("Você saiu do Minishelly!\n");
	clean_strlist(&mini->prompt);
	clean_strlist(&mini->env);
	clean_strlist(&mini->path);
	if (mini->new_parser)
		free(mini->new_parser);
	if (mini->str)
		free(mini->str);
	ft_token_free(&mini->tokens);
	if (mini->exec)
	{
		int i = 0;
		while (i < mini->exec->pipes)
		{
			if (mini->exec->fd[i])
				free(mini->exec->fd[i]);
			i++;
		}
		if (mini->exec->fd)
			free(mini->exec->fd);
		free(mini->exec->func);
		free(mini->exec);
		mini->exec = NULL;
	}
	if (mini)
		free(mini);
	exit(EXIT_SUCCESS);
}
