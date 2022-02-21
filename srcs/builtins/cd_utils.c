/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:53:07 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:53:08 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	chdir_error_permission(char *dir)
{
	write(2, "cd: Permission denied: ", 23);
	ft_putendl_fd(dir, 2);
}

void	chdir_error(char *dir)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	write(2, ": ", 2);
	ft_putendl_fd(dir, 2);
}

int	print_absolute_path(char *cdpath_dir)
{
	char	*dir;

	free(cdpath_dir);
	dir = getcwd(NULL, 0);
	if (!dir)
		return (1);
	ft_putendl_fd(dir, 1);
	free(dir);
	return (1);
}

char	**explore_cdpath(char *dir)
{
	if (ft_strncmp(dir, "..\0", 3) == 0 || ft_strncmp(dir, "../", 3) == 0 \
		|| ft_strncmp(dir, ".\0", 2) == 0 || ft_strncmp(dir, "./", 2) == 0 \
		|| dir[0] == '/' || !getenv("CDPATH"))
		return (NULL);
	return (ft_split(getenv("CDPATH"), ':'));
}

char	*path_join(char *cdpath, char *dir)
{
	int		len;
	char	*cdpath_dir;

	len = ft_strlen(cdpath);
	if (cdpath[len - 1] != '/')
		cdpath_dir = ft_strjoin_3(cdpath, "/", dir);
	else
		cdpath_dir = ft_strjoin(cdpath, dir);
	return (cdpath_dir);
}
