/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_outputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:54:36 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:54:37 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_filedes(t_ioredir *redir)
{
	if (access(redir->str, F_OK) == 0)
	{
		if (access(redir->str, W_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(redir->str, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putchar_fd('\n', 2);
			return (-1);
		}
	}
	if (redir->type == 1)
		redir->fd = open(redir->str, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == 2)
		redir->fd = open(redir->str, O_RDWR | O_CREAT | O_APPEND, 0644);
	return (0);
}

static char	*read_buffer(int fd_read)
{
	char		*buf;
	char		*line;
	char		*tmp;

	buf = NULL;
	while (1)
	{
		line = get_next_line(fd_read);
		if (!line)
			break ;
		if (!buf)
			buf = ft_strdup("");
		tmp = ft_strjoin(buf, line);
		free(buf);
		free(line);
		buf = tmp;
	}
	close(fd_read);
	return (buf);
}

int	output_redirections(t_cmd *cmd, int fd_read)
{
	int			stdin_fd;
	char		*buf;
	t_ioredir	*current;
	t_ioredir	*next;
	ssize_t		n;

	stdin_fd = dup(STDIN_FILENO);
	buf = read_buffer(fd_read);
	current = cmd->first_out_redir;
	while (current)
	{
		next = current->next;
		if (open_filedes(current) == -1)
			return (-1);
		n = write(current->fd, buf, ft_strlen(buf));
		if (n == -1)
			ft_putstr_fd(strerror(errno), 2);
		close(current->fd);
		current = next;
	}
	dup2(stdin_fd, STDIN_FILENO);
	close(stdin_fd);
	return (0);
}
