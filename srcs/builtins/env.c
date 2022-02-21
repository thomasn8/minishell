/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:53:26 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:53:27 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		ft_putstr_fd(line, 1);
	}
	close(fd);
}

int	env_builtin(t_cmd *cmd)
{
	int		start;
	int		fd;
	char	*dir;

	start = first_nonempty_arg(cmd->args);
	if (start > 0)
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (BUILTIN_FAILURE);
	}
	fd = -1;
	dir = ft_strjoin_3(getenv("HOME"), "/", ENVS_FILE);
	fd = open(dir, O_RDONLY);
	if (fd < 0)
	{
		free(dir);
		return (PERMISSION_ERROR);
	}
	print_env(fd);
	free(dir);
	return (0);
}
