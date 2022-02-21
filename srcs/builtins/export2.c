/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:53:42 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:53:43 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*add_last_newline(char *buf_before)
{
	char	*tmp;

	tmp = ft_strjoin(buf_before, "\n");
	free (buf_before);
	buf_before = tmp;
	return (buf_before);
}

// si modify_env a break au strncmp (et donc on a l'ancienne VAR dans prev_line)
static char	*insert_inside_buf(int fd, char *buf_before, char *new_line)
{
	char	*line;
	char	*buf_after;
	char	*buf;

	buf_before = ft_strjoin(buf_before, new_line);
	buf_after = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!buf_after)
			buf_after = ft_strdup("");
		buf = ft_strjoin(buf_after, line);
		free(buf_after);
		free(line);
		buf_after = buf;
	}
	if (!buf_after)
		return (add_last_newline(buf_before));
	buf = ft_strjoin_3(buf_before, "\n", buf_after);
	free(buf_before);
	free(buf_after);
	return (buf);
}

// insert au milieu du buf ou write à la fin (selon break dans new_env)
static char	*append_or_insert(char *line, int fd, \
			char *buf_before, char **key_value)
{
	char	*new_line;
	char	*buf;

	if (key_value[1])
		new_line = ft_strjoin(key_value[0], key_value[1]);
	else
		new_line = ft_strdup(key_value[0]);
	ft_free_arr(key_value);
	if (line)
	{
		free(line);
		buf = insert_inside_buf(fd, buf_before, new_line);
		free(new_line);
		return (buf);
	}
	free(buf_before);
	write(fd, new_line, ft_strlen(new_line));
	write(fd, "\n", 1);
	free(new_line);
	return (NULL);
}

// read .minishell_profile jusqu'a la ligne contenant la var à exporter
static char	*search_key(char **key_value, int fd)
{
	char	*line;
	char	*buf_before;
	int		len;
	char	*tmp;

	buf_before = NULL;
	len = ft_strlen(key_value[0]);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (strncmp(key_value[0], line, len) == 0)
			break ;
		if (!buf_before)
			buf_before = ft_strdup("");
		tmp = ft_strjoin(buf_before, line);
		free(buf_before);
		free(line);
		buf_before = tmp;
	}
	return (append_or_insert(line, fd, buf_before, key_value));
}

void	split_key_value(char *arg, int *fd, char *dir)
{
	char	**key_value;
	char	*key;
	char	*tmp;
	char	*buf;

	key_value = ft_split(arg, '=');
	if (key_value)
	{
		key = ft_strjoin(key_value[0], "=");
		tmp = key_value[0];
		key_value[0] = key;
		free (tmp);
		if (key_value[1] || arg[ft_strlen(arg) - 1] == '=')
		{
			buf = search_key(key_value, *fd);
			if (buf)
			{
				close(*fd);
				*fd = open(dir, O_RDWR | O_TRUNC, 0644);
				write(*fd, buf, ft_strlen(buf));
				free(buf);
			}
		}
	}
}
