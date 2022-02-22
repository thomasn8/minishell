/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:54:23 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/22 15:04:34 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_fildes(int *p)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("read: ", 2);
	ft_putnbr_fd(p[0], 2);
	ft_putstr_fd(" | write: ", 2);
	ft_putnbr_fd(p[1], 2);
	ft_putstr_fd(WHI, 2);
	ft_putstr_fd("\n", 2);
}

static int	wait_child(int *status)
{
	pid_t	id_child;

	id_child = waitpid(g_child, status, 0);
	if (id_child == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (EXIT_FAILURE);
	}
	if (WIFEXITED(*status))
	{
		*status = WEXITSTATUS(*status);
		g_child = NO_CHILD_P;
	}
	return (0);
}

static void	child_exec(t_cmd *cmd, char **env, int n, int *cmd_pipe, int stdin_fd)
{
	g_child = fork();
	if (g_child == 0)
	{
		if (cmd->first_in_redir != NULL)
			input_redirections(cmd, stdin_fd);
		if (n != LAST || cmd->first_out_redir)
			dup2(cmd_pipe[1], STDOUT_FILENO);
		close(cmd_pipe[0]);
		close(cmd_pipe[1]);
		if (cmd->name)
			simple_cmd(cmd, env);
		free_cmds(cmd);
		exit(NO_NAME);
	}
}

static void	main_exec(t_cmd *cmd, char **env, int n, int *status, int stdin_fd)
{
	int		cmd_pipe[2];

	pipe(cmd_pipe);
	print_fildes(cmd_pipe);
	if (is_builtin(cmd))
	{
		if (n != LAST)
			dup2(cmd_pipe[1], STDOUT_FILENO);
		builtins(cmd, STDOUT_FILENO);
	}
	else
	{
		child_exec(cmd, env, n, cmd_pipe, stdin_fd);
		wait_child(status);
	}
	dup2(cmd_pipe[0], STDIN_FILENO);
	close(cmd_pipe[0]);
	close(cmd_pipe[1]);
	if (cmd->first_out_redir != NULL)
		output_redirections(cmd, STDIN_FILENO);
}

void	execution(t_cmd *current, char **env, int n, int *status)
{
	int		stdin_fd;
	int		stdout_fd;

	stdin_fd = dup(STDIN_FILENO);
	stdout_fd = dup(STDOUT_FILENO);
	while (n--)
	{
		dup2(stdout_fd, STDOUT_FILENO);
		main_exec(current, env, n, status, stdin_fd);
		current = current->next;
	}
	dup2(stdin_fd, STDIN_FILENO);
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdin_fd);
	close(stdout_fd);
}
