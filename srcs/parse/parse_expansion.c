/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:55:16 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:55:16 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	shift_first_arg(t_cmd *cmd)
{
	char	*tmp;

	while (cmd->args[0] && *cmd->args[0] == '\0')
	{
		if (cmd->args[1])
			remove_first(cmd->args);
		else
		{
			tmp = cmd->args[0];
			cmd->args[0] = NULL;
			free(tmp);
			tmp = cmd->name;
			cmd->name = NULL;
			free(tmp);
		}
	}
	tmp = cmd->name;
	if (cmd->args[0])
		cmd->name = ft_strdup(cmd->args[0]);
	free(tmp);
}

static void	expansion_redir(t_ioredir *first_redir)
{
	t_ioredir	*current;
	t_ioredir	*next;

	current = first_redir;
	while (current)
	{
		next = current->next;
		current->str = expansion_component(current->str, NULL);
		current = next;
	}
}

static void	components(t_cmd *cmd, int *status)
{
	int	i;

	if (cmd->name)
		cmd->name = expansion_component(cmd->name, status);
	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			cmd->args[i] = expansion_component(cmd->args[i], status);
			i++;
		}
		if (*cmd->args[0] == '\0')
			shift_first_arg(cmd);
	}
	if (cmd->first_in_redir != NULL)
		expansion_redir(cmd->first_in_redir);
	if (cmd->first_out_redir != NULL)
		expansion_redir(cmd->first_out_redir);
}

void	expansion(t_cmd *first_cmd, int *status)
{
	t_cmd	*current;
	t_cmd	*next;

	current = first_cmd;
	while (current)
	{
		next = current->next;
		components(current, status);
		current = next;
	}
}
