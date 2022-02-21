/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:53:37 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:53:38 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	invalid_identifier(char *arg, int *error, int builtin)
{	
	ft_putstr_fd("minishell: ", 2);
	if (builtin == 1)
		ft_putstr_fd("export: `", 2);
	else
		ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	*error = BUILTIN_FAILURE;
}

// alpha[alphanum-underscore]=[isprint-\t]
static int	check_format(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]))
		return (-1);
	i++;
	while (arg[i])
	{
		if (arg[i] == '=')
			break ;
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (-1);
		i++;
	}
	while (arg[i])
	{
		if (!ft_isprint(arg[i]) && arg[i] != '\t')
			return (-1);
		i++;
	}
	return (0);
}

int	export(t_cmd *cmd)
{
	int		fd;
	char	*dir;
	int		error;
	int		i;

	fd = -1;
	dir = ft_strjoin_3(getenv("HOME"), "/", ENVS_FILE);
	error = 0;
	i = 0;
	while (cmd->args[++i])
	{
		if (check_config_file(dir, &fd, 2, ".minishell_env"))
		{
			free(dir);
			return (PERMISSION_ERROR);
		}
		if (check_format(cmd->args[i]) == 0)
			split_key_value(cmd->args[i], &fd, dir);
		else
			invalid_identifier(cmd->args[i], &error, 1);
	}
	close(fd);
	free(dir);
	return (error);
}
