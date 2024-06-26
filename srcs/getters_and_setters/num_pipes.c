/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:49:53 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/25 22:30:18 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	*get_is_fork(void)
{
	static int	num;

	return (&num);
}

int	*get_num_pipes(void)
{
	static int	num;

	return (&num);
}

void	set_num_pipes(int num)
{
	int	*sc;

	sc = get_num_pipes();
	*sc = num;
}

t_sys_config	**get_ms(void)
{
	static t_sys_config	*ms;

	return (&ms);
}
