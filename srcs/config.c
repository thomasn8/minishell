/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:56:38 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:56:39 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_value(char *key, int *fd)
{
	char	*line;
	int		len;
	char	*value;
	char	*tmp;

	len = ft_strlen(key);
	while (1)
	{
		line = get_next_line(*fd);
		if (!line)
			break ;
		if (strncmp(key, line, len) == 0)
			break ;
		free(line);
	}
	if (!line)
		return (NULL);
	len = 0;
	while (line[len] != '=')
		len++;
	tmp = ft_cut_strnstr((const char *)line, 0, len + 1);
	free(line);
	value = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
	free(tmp);
	return (value);
}

char	*get_minishell_env(char *key)
{
	int		fd;
	char	*dir;
	char	*value;

	dir = ft_strjoin_3(getenv("HOME"), "/", ENVS_FILE);
	fd = open(dir, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: impossible to open '", 2);
		ft_putstr_fd(dir, 2);
		ft_putendl_fd("'", 2);
		free(dir);
		return (NULL);
	}
	value = get_value(key, &fd);
	close(fd);
	free(dir);
	return (value);
}

int	check_config_file(char *dir, int *fd, int mask, char *filename)
{
	if (access(dir, F_OK) == 0)
	{
		if (access(dir, R_OK) == -1 || access(dir, W_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(filename, 2);
			ft_putstr_fd(": permission denied in ", 2);
			ft_putendl_fd(getenv("HOME"), 2);
			return (-1);
		}
	}
	if (mask == 1)
		*fd = open(dir, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		*fd = open(dir, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
	{
		ft_putstr_fd("minishell: impossible to open '", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd("' in ", 2);
		ft_putendl_fd(getenv("HOME"), 2);
		return (-1);
	}
	return (0);
}

static void	write_envs(char **env, int fd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		write(fd, env[i], ft_strlen(env[i]));
		write(fd, "\n", 1);
		i++;
	}
}

int	config(int ac, char **av, char **env, int *status)
{
	char	*dir_env;
	char	*dir_hist;
	int		error;
	int		fd_env;
	int		fd_hist;

	(void) ac;
	(void) av;
	error = 0;
	status = 0;
	dir_env = ft_strjoin_3(getenv("HOME"), "/", ENVS_FILE);
	dir_hist = ft_strjoin_3(getenv("HOME"), "/", HIST_FILE);
	if (check_config_file(dir_env, &fd_env, 1, ".minishell_env"))
		error -= 1;
	else
		write_envs(env, fd_env);
	if (check_config_file(dir_hist, &fd_hist, 2, ".minishell_history"))
		error -= 2;
	close(fd_env);
	close(fd_hist);
	free(dir_env);
	free(dir_hist);
	return (error);
}
