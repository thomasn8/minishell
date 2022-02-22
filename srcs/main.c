/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:56:52 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/22 13:41:29 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	int			status;
	t_t			term;
	int			n;
	char		*cmd;
	t_cmd		*first_cmd;

	config(ac, av, env, &status);
	g_child = NO_CHILD_P;
	init_signals(&term);
	while (1)
	{
		n = 0;
		if (g_child == NO_CHILD_P)
			cmd = prompt();
		if (cmd == NULL)
			break ;
		first_cmd = parsing(cmd, &n, &status);
		if (first_cmd)
		{
			execution(first_cmd, env, n, &status);
			free_cmds(first_cmd);
		}
	}
	stop(0, &term);
}
