/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:57:02 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/22 13:35:35 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_signals(t_t *term)
{
	int	ret;

	ret = tcgetattr(STDIN_FILENO, &term->termios_save);
	if (ret)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	term->termios_new = term->termios_save;
	term->termios_new.c_lflag &= ~ECHOCTL;
	ret = tcsetattr(STDIN_FILENO, 0, &term->termios_new);
	if (ret)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	signal(SIGINT, ctrlc_signal);
	signal(SIGQUIT, ctrlslash_signal);
}

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
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ctrlslash_signal(int sig)
{
	(void) sig;
}

void	stop(int exit_code, t_t *term)
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
	rl_clear_history();
	tcsetattr(STDIN_FILENO, 0, &term->termios_save);
	ft_putstr_fd("logout\n", 1);
	exit(exit_code);
}
