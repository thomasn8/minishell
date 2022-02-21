/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:53:55 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:53:57 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	rewrite_file(int *fd, char *buf, char *dir)
{
	close(*fd);
	*fd = open(dir, O_WRONLY | O_TRUNC);
	write(*fd, buf, ft_strlen(buf));
	return (0);
}

static int	join_before_after(int *fd, char *buf_before, char *dir)
{
	char	*line;
	char	*buf_after;
	char	*buf;
	char	*tmp;

	buf_after = NULL;
	while (1)
	{
		line = get_next_line(*fd);
		if (!line)
			break ;
		if (!buf_after)
			buf_after = ft_strdup("");
		tmp = ft_strjoin(buf_after, line);
		free(buf_after);
		free(line);
		buf_after = tmp;
	}
	if (!buf_after)
		return (rewrite_file(fd, buf_before, dir));
	buf = ft_strjoin(buf_before, buf_after);
	free(buf_before);
	free(buf_after);
	return (rewrite_file(fd, buf, dir));
}

static int	get_line(char *arg, int *fd, char *dir)
{
	char	*line;
	char	*buf_before;
	int		len;
	char	*tmp;

	buf_before = NULL;
	len = ft_strlen(arg);
	while (1)
	{
		line = get_next_line(*fd);
		if (!line)
			break ;
		if (strncmp(arg, line, len) == 0)
			break ;
		if (!buf_before)
			buf_before = ft_strdup("");
		tmp = ft_strjoin(buf_before, line);
		free(buf_before);
		free(line);
		buf_before = tmp;
	}
	if (!line)
		return (1);
	free(line);
	return (join_before_after(fd, buf_before, dir));
}

static int	check_format(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]))
		return (-1);
	i++;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (-1);
		i++;
	}
	return (0);
}

int	unset(t_cmd *cmd)
{
	int		fd;
	char	*dir;
	int		i;
	int		error;

	dir = ft_strjoin_3(getenv("HOME"), "/", ENVS_FILE);
	i = 0;
	error = 0;
	while (cmd->args[++i])
	{
		fd = open(dir, O_RDONLY);
		if (fd < 0)
			free(dir);
		if (fd < 0)
			return (PERMISSION_ERROR);
		if (check_format(cmd->args[i]) == 0)
		{
			get_line(cmd->args[i], &fd, dir);
			close(fd);
		}
		else
			invalid_identifier(cmd->args[i], &error, 2);
	}
	free(dir);
	return (error);
}
