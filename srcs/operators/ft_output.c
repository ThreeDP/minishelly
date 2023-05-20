/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:03:37 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/20 16:01:51 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_output(t_sys_config *ms)
{
	int				fd;
	int				bkp;
	t_process_func	*func;

	bkp = dup(1);
	if (bkp == -1)
		sys_exit(clean_data, EBADF, ms);
	func = ms->exec->func;
	if (run_access(ms->tokens->token[1], W_OK))
	{
		fd = open(ms->tokens->token[1], O_WRONLY | O_TRUNC);
		if (fd == -1)
			return (set_status_code(1), 1);
	}
	else
	{
		if (*get_status_code() == 126)
		{
			fd = open(ms->tokens->token[1], O_WRONLY | O_CREAT,  0644);
			if (fd == -1)
				return (set_status_code(1), 1);
		}
		else
			return (set_status_code(1), 1);
	}
	if (ms->tokens->next)
	{
		ms->tokens = ms->tokens->next;
		dup2(fd, 1);
		close(fd);
		func[ms->tokens->type](ms);
		close(1);
		dup2(bkp, 1);
	}
	return (0);
}
