/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:57:02 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/22 02:50:44 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrlc_signal(int sig)
{
	int		success;

	if (g_child == 0)
		exit(sig);
	write(1, "\n", 1);
	if (g_child > 0)
	{
		success = kill(g_child, sig);
		if (success == -1)
		{
			ft_putstr_fd("Impossible to kill g_child process\n", 2);
			exit(KILL_ERROR);
		}
		g_child = NO_CHILD_P;
	}
	else
		print_prompt();
}

void	ctrlslash_signal(int sig)
{
	(void) sig;
	ft_putstr_fd("\b\b  \b\b", 1);
}

void	stop(int exit_code)
{
	int	success;

	if (g_child > 0)
	{
		success = kill(g_child, SIGKILL);
		if (success == -1)
		{
			ft_putstr_fd("Error trying to kill g_child process n° \n", 2);
			ft_putnbr_fd(g_child, 2);
			exit(KILL_ERROR);
		}
	}
	ft_putstr_fd("logout\n", 1);
	exit(exit_code);
}
