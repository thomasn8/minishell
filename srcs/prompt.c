/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:56:56 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:56:57 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*print_user(void)
{
	char	*user;

	user = ft_strdup(getenv("USER"));
	if (!user)
		exit(BUILTIN_FAILURE);
	ft_putstr_fd(user, 1);
	return (user);
}

static char	*print_relative_dir(void)
{
	char	*absolute_dir;
	char	*home;
	int		len;
	char	*custom;

	absolute_dir = getcwd(NULL, 0);
	if (!absolute_dir)
		exit(BUILTIN_FAILURE);
	home = getenv("HOME");
	if (!home)
		exit(BUILTIN_FAILURE);
	len = ft_strlen(home);
	custom = ft_strnstr(absolute_dir, home, len);
	if (custom)
	{
		write(1, "~", 1);
		if (absolute_dir != home)
			ft_putstr_fd(&custom[len], 1);
	}
	else
		ft_putstr_fd(absolute_dir, 1);
	return (absolute_dir);
}

char	*prompt(void)
{
	char	*user;
	char	*absolute_dir;

	absolute_dir = NULL;
	user = print_user();
	write(1, ":", 1);
	absolute_dir = print_relative_dir();
	ft_putstr_fd(" $ ", 1);
	free(user);
	free(absolute_dir);
	return (get_cmd_line(STDIN_FILENO));
}

void	print_prompt(void)
{
	char	*user;
	char	*absolute_dir;

	absolute_dir = NULL;
	user = print_user();
	write(1, ":", 1);
	absolute_dir = print_relative_dir();
	ft_putstr_fd(" $ ", 1);
	free(user);
	free(absolute_dir);
}
