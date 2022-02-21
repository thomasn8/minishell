/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:55:06 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:55:06 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	write_history(int fd, char *cmd, int nbr_cmd)
{
	ft_putnbr_fd(nbr_cmd, fd);
	write(fd, "  ", 2);
	write(fd, cmd, ft_strlen(cmd));
	write(fd, "\n", 1);
}

int	history(char *cmd)
{
	int		fd;
	char	*dir;
	int		nbr_cmd;
	char	*line;

	nbr_cmd = 0;
	dir = ft_strjoin_3(getenv("HOME"), "/", HIST_FILE);
	fd = open(dir, O_RDWR | O_APPEND);
	if (fd == -1)
		return (PERMISSION_ERROR);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		nbr_cmd++;
	}
	write_history(fd, cmd, nbr_cmd);
	close(fd);
	free(dir);
	return (0);
}
