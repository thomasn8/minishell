/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:54:27 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:54:28 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	no_relative_path(char *name)
{
	char	*path;

	if (ft_strnstr(name, "/", ft_strlen(name)))
		return (1);
	path = get_minishell_env("PATH");
	if (!path)
		return (1);
	free(path);
	return (0);
}

static char	*find_path(char *name)
{
	char	**paths;
	char	*path;
	char	*slash;
	int		i;

	if (no_relative_path(name))
		return (name);
	path = get_minishell_env("PATH");
	paths = ft_split(path, ':');
	free(path);
	i = -1;
	while (paths[++i])
	{
		slash = ft_strjoin(paths[i], "/");
		path = ft_strjoin(slash, name);
		free(slash);
		if (access(path, F_OK) == 0)
		{
			ft_free_arr(paths);
			return (path);
		}
		free(path);
	}
	ft_free_arr(paths);
	return (NULL);
}

int	command_not_found(t_cmd *cmd)
{
	write(2, "minishell: ", 11);
	ft_putstr_fd(cmd->name, 2);
	write(2, ": command not found\n", 20);
	free_cmds(cmd);
	exit(CMD_NOT_FOUND);
}

static void	exec_impossible(t_cmd *cmd, int error_type)
{
	if (error_type == CMD_NOT_FOUND)
		command_not_found(cmd);
	write(2, "minishell: ", 11);
	ft_putstr_fd(cmd->name, 2);
	write(2, ": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	free_cmds(cmd);
	exit(FATAL_SIGNAL + errno);
}

void	simple_cmd(t_cmd *cmd, char **env)
{
	char	*path;

	path = find_path(cmd->name);
	if (path == NULL)
		exec_impossible(cmd, CMD_NOT_FOUND);
	if (execve(path, cmd->args, env) == -1)
		exec_impossible(cmd, CMD_NOT_EXECUTABLE);
}
