/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:53:49 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/22 13:38:28 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(void)
{
	int		exit_code;
	char	*dir;

	exit_code = 0;
	dir = getcwd(NULL, 0);
	if (!dir)
		exit_code = BUILTIN_FAILURE;
	else
		ft_putendl_fd(dir, 1);
	free(dir);
	return (exit_code);
}
