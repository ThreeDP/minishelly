/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:45:46 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/14 15:36:15 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_input(t_sys_config * ms)
{
	int				fd;
	int				bkp;
	t_process_func	*func;

	bkp = dup(0);
	if (bkp == -1)
		sys_exit(clean_data, EBADF, ms);
	func = ms->exec->func;
	fd = open(ms->tokens->token[1], O_RDONLY);
	if (fd == -1)
		sys_exit(clean_data, ENOENT, ms);
	if (ms->tokens->next)
	{
		ms->tokens = ms->tokens->next;
		if (dup2(fd, 0) == -1)
			sys_exit(clean_data, EBADF, ms);
		close(fd);
		func[ms->tokens->type](ms);
		close(1);
		if (dup2(bkp, 0) == -1)
			sys_exit(clean_data, EBADF, ms);
	}
	return (ms->tokens->type);
}