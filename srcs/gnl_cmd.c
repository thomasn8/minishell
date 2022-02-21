/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:56:47 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:56:48 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*return_next_line(char **s)
{
	char	*out;
	char	*tmp;
	size_t	len;

	len = 0;
	out = NULL;
	while ((*s)[len] != '\n' && (*s)[len])
		len++;
	if ((*s)[len] == '\n')
	{
		out = ft_substr(*s, 0, len + 1);
		tmp = ft_strdup(*s + len + 1);
		free(*s);
		*s = tmp;
		if (!**s)
		{
			free(*s);
			*s = NULL;
		}
		return (out);
	}
	out = ft_strdup(*s);
	free(*s);
	*s = NULL;
	return (out);
}

static void	read_again(char *prev, int *pipe_fd)
{
	char	*line;

	close(pipe_fd[0]);
	line = get_next_line(STDIN_FILENO);
	write(pipe_fd[1], prev, ft_strlen(prev));
	write(pipe_fd[1], line, ft_strlen(line));
	dup2(pipe_fd[1], STDOUT_FILENO);
	free(line);
	free(prev);
	exit(EXIT_SUCCESS);
}

static char	*check_and_return(char **s, ssize_t n)
{
	int		pipe_fd[2];
	char	*tmp;
	char	*line;

	if (n < 0 || (!n && (!s || !*s)))
		return (NULL);
	if (n)
		return (return_next_line(s));
	pipe(pipe_fd);
	tmp = ft_strdup(*s);
	free(*s);
	*s = NULL;
	g_child = fork();
	if (g_child == 0)
		read_again(tmp, pipe_fd);
	close(pipe_fd[1]);
	waitpid(g_child, NULL, 0);
	free(tmp);
	line = get_cmd_line(pipe_fd[0]);
	if (!line)
		return (ft_strdup(""));
	return (line);
}

char	*get_cmd_line(int fd)
{
	char		*tmp;
	char		*buf;
	static char	*s;
	ssize_t		n;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	n = read(fd, buf, BUFFER_SIZE);
	while (n > 0)
	{
		buf[n] = '\0';
		if (!s)
			s = ft_strdup("");
		tmp = ft_strjoin(s, buf);
		free(s);
		s = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
		n = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (check_and_return(&s, n));
}
