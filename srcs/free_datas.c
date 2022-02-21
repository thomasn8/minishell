/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_datas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:56:43 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:56:44 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_redir_list(t_ioredir *first)
{
	t_ioredir	*current;
	t_ioredir	*next;

	current = first;
	while (current)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
}

static void	free_components(t_cmd *cmd)
{
	if (cmd->name)
		free(cmd->name);
	if (cmd->args)
		ft_free_arr(cmd->args);
	if (cmd->first_in_redir != NULL)
		free_redir_list(cmd->first_in_redir);
	if (cmd->first_out_redir != NULL)
		free_redir_list(cmd->first_out_redir);
}

static void	free_all(t_cmd *first_cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	if (first_cmd)
	{
		current = first_cmd;
		while (current)
		{
			next = current->next;
			free_components(current);
			free(current);
			current = next;
		}
	}
}

int	free_cmds(t_cmd *cmd)
{
	while (cmd->prev)
		cmd = cmd->prev;
	free_all(cmd);
	return (0);
}
