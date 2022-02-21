/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:53:31 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:53:32 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exit_builtin(t_cmd *cmd)
{
	int		start;
	int		exit_code;

	exit_code = 0;
	start = first_nonempty_arg(cmd->args);
	if (start > 0)
		exit_code = 255;
	ft_putstr_fd("logout\n", 1);
	exit(exit_code);
}
