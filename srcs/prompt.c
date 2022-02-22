/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:56:56 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/22 13:37:05 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_user(void)
{
	char	*user;

	user = ft_strdup(getenv("USER"));
	return (user);
}

static char	*get_relative_dir(void)
{
	char	*absolute_dir;
	char	*home;
	int		len;
	char	*custom;

	absolute_dir = getcwd(NULL, 0);
	home = getenv("HOME");
	len = ft_strlen(home);
	custom = ft_strnstr(absolute_dir, home, len);
	if (!custom)
		return (absolute_dir);
	if (absolute_dir == home)
		return (ft_strdup("~"));
	return (ft_strjoin("~", &custom[len]));
}

char	*prompt(void)
{
	char		*user;
	char		*dir;
	char		*tmp;
	static char	*cmd = NULL;

	user = get_user();
	tmp = ft_strjoin(user, ":");
	free(user);
	user = tmp;
	dir = get_relative_dir();
	tmp = ft_strjoin(dir, " $ ");
	free(dir);
	dir = tmp;
	tmp = ft_strjoin(user, dir);
	free(user);
	free(dir);
	if (cmd)
	{
		free(cmd);
		cmd = NULL;
	}
	cmd = readline(tmp);
	free(tmp);
	return (cmd);
}
