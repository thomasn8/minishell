/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:53:20 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:53:20 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	echo_newline(void)
{
	ft_putstr_fd("\n", 1);
	return (0);
}

int	echo(t_cmd *cmd)
{
	int	i;
	int	start;
	int	newline;

	start = first_nonempty_arg(cmd->args);
	if (start == -1)
		return (echo_newline());
	newline = 1;
	if (ft_strncmp(cmd->args[start], "-n\0", 3) == 0)
	{
		newline = 0;
		start++;
	}
	i = 0;
	while (cmd->args[start + i] && cmd->args[start + i + 1])
	{
		ft_putstr_fd(cmd->args[start + i], 1);
		write(1, " ", 1);
		i++;
	}
	ft_putstr_fd(cmd->args[start + i], 1);
	if (newline == 1)
		write(1, "\n", 1);
	return (0);
}
