/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:54:32 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:54:33 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	read_terminal_lines(char *limiter, int fd_write)
{
	char	*line;
	char	*limiter_nl;
	int		len;

	limiter_nl = ft_strjoin(limiter, "\n");
	len = ft_strlen(limiter) + 1;
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter_nl, len) == 0
			|| ft_strncmp(line, limiter, len) == 0)
		{
			free(limiter_nl);
			free(line);
			exit(EXIT_SUCCESS);
		}
		write(fd_write, line, ft_strlen(line));
		free(line);
	}
}

static void	double_r(char *limiter, int fd_write)
{
	pid_t	grandchild;

	grandchild = fork();
	if (grandchild == -1)
		exit(REDIR_ERROR);
	if (grandchild == 0)
		read_terminal_lines(limiter, fd_write);
	else
		waitpid(grandchild, NULL, 0);
}

static void	simple_r(t_ioredir *redir, int fd_write)
{
	char	*line;

	if (access(redir->str, R_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		exit(PERMISSION_ERROR);
	}
	redir->fd = open(redir->str, O_RDONLY);
	if (redir->fd == -1)
		exit(REDIR_ERROR);
	while (1)
	{
		line = get_next_line(redir->fd);
		if (!line)
			break ;
		write(fd_write, line, ft_strlen(line));
		free(line);
	}
	close(redir->fd);
}

// bash prend en compte que 1 input redirection, la dernière
void	input_redirections(t_cmd *cmd)
{
	int			input_pipe[2];
	t_ioredir	*current;
	t_ioredir	*next;

	pipe(input_pipe);
	current = cmd->first_in_redir;
	while (current)
	{
		if (current->next == NULL)
			break;
		next = current->next;
		current = next;
	}
	if (current->type == 1)
		simple_r(current, input_pipe[1]);
	else if (current->type == 2)
		double_r(current->str, input_pipe[1]);
	dup2(input_pipe[0], STDIN_FILENO);
	close(input_pipe[0]);
	close(input_pipe[1]);
}
