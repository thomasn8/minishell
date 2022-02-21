/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:53:13 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:53:14 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cdpath_search(char *dir)
{
	char	**cdpaths;
	int		i;
	int		permission;
	char	*cdpath_dir;

	cdpaths = explore_cdpath(dir);
	if (!cdpaths)
		return (0);
	i = 0;
	permission = 0;
	while (cdpaths[i])
	{
		cdpath_dir = path_join(cdpaths[i], dir);
		if (chdir(cdpath_dir) == 0)
			return (print_absolute_path(cdpath_dir));
		if (access(cdpath_dir, F_OK) == 0 && access(cdpath_dir, X_OK) == -1)
			permission = -1;
		free(cdpath_dir);
		i++;
	}
	if (permission == -1 && chdir(dir) == 0)
		return (print_absolute_path(NULL));
	if (permission == -1)
		return (-1);
	return (0);
}

static char	*first_arg_dir(t_cmd *cmd, int *error)
{
	char	*dir;
	int		start;

	start = first_nonempty_arg(cmd->args);
	if (start == -1)
	{
		dir = getenv("HOME");
		if (!dir)
		{
			*error = 1;
			return (NULL);
		}
		chdir(dir);
		return (NULL);
	}
	dir = ft_strdup(cmd->args[start]);
	return (dir);
}

static int	free_and_return(char *dir, int failure)
{
	free(dir);
	if (failure == 1)
		return (BUILTIN_FAILURE);
	return (0);
}

int	cd(t_cmd *cmd)
{
	char	*dir;
	int		cdpath;
	int		failure;
	int		error;

	error = 0;
	dir = first_arg_dir(cmd, &error);
	if (error)
		return (BUILTIN_FAILURE);
	if (!dir)
		return (0);
	failure = 0;
	cdpath = cdpath_search(dir);
	if (cdpath == -1)
	{
		chdir_error_permission(dir);
		failure = 1;
	}
	if (cdpath == 0 && chdir(dir) == -1)
	{
		chdir_error(dir);
		failure = 1;
	}
	return (free_and_return(dir, failure));
}
