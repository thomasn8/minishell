/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:53:01 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/22 13:38:46 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(t_cmd *current)
{
	if (current->name)
	{
		if (ft_strncmp(current->name, "cd\0", 3) == 0)
			return (1);
		else if (ft_strncmp(current->name, "exit\0", 5) == 0)
			return (1);
		else if (ft_strncmp(current->name, "export\0", 7) == 0)
			return (1);
		else if (ft_strncmp(current->name, "unset\0", 6) == 0)
			return (1);
		else if (ft_strncmp(current->name, "pwd\0", 4) == 0)
			return (1);
		else if (ft_strncmp(current->name, "echo\0", 5) == 0)
			return (1);
		else if (ft_strncmp(current->name, "env\0", 4) == 0)
			return (1);
	}
	return (0);
}

void	builtins(t_cmd *current, int fd)
{
	if (ft_strncmp(current->name, "cd\0", 3) == 0)
		cd(current);
	else if (ft_strncmp(current->name, "exit\0", 5) == 0)
		exit_builtin(current);
	else if (ft_strncmp(current->name, "export\0", 7) == 0)
		export(current);
	else if (ft_strncmp(current->name, "unset\0", 6) == 0)
		unset(current);
	else if (ft_strncmp(current->name, "pwd\0", 4) == 0)
		pwd();
	else if (ft_strncmp(current->name, "echo\0", 5) == 0)
		echo(current);
	else if (ft_strncmp(current->name, "env\0", 4) == 0)
		env_builtin(current);
	close(fd);
}

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
