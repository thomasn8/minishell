/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:52:53 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:52:57 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	first_nonempty_arg(char **args)
{
	int	i;

	i = 1;
	if (args)
	{
		while (args[i] && !(args[i][0]))
			i++;
		if (!args[i])
			return (-1);
		return (i);
	}
	return (-1);
}
