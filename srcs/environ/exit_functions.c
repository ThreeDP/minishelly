/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:51:33 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/25 17:51:48 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	normal_exit(void (*f)(void *), int exit_code, void *item)
{
	ft_putstr_fd(strerror(exit_code), 2);
	write(2, "\n", 1);
	exit(exit_code);
	f(item);
}

void	sys_exit(void (*f)(t_sys_config *), int exit_code, t_sys_config *mini)
{
	ft_printf("%s\n", strerror(exit_code));
	exit(exit_code);
	f(mini);
}

void	sys_exit_err(void (*f)(t_sys_config *), t_sys_config *mini, char *msg)
{
	if (!msg)
	{
		perror(" ");
		write(2, "\n", 1);
	}
	else
	{
		ft_putstr_fd(msg, 2);
		write(2, "\n", 1);
	}
	f(mini);
	exit (*get_status_code());
}
