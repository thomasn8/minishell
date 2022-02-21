/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:55:26 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:55:27 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*cmd_list_create(int n)
{
	t_cmd	*cmd;
	t_cmd	*tmp_next;
	t_cmd	*tmp_prev;

	cmd = NULL;
	tmp_next = NULL;
	tmp_prev = NULL;
	while (n--)
	{
		cmd = malloc(sizeof(t_cmd));
		if (tmp_prev)
			tmp_prev->prev = cmd;
		tmp_prev = cmd;
		cmd->order = n + 1;
		cmd->next = tmp_next;
		tmp_next = cmd;
		cmd->name = NULL;
		cmd->args = NULL;
		cmd->first_in_redir = NULL;
		cmd->first_out_redir = NULL;
	}
	cmd->prev = NULL;
	return (cmd);
}

t_ioredir	*io_list_create(int n)
{
	t_ioredir	*redir;
	t_ioredir	*tmp_next;
	t_ioredir	*tmp_prev;

	redir = NULL;
	tmp_next = NULL;
	tmp_prev = NULL;
	while (n--)
	{
		redir = malloc(sizeof(t_ioredir));
		if (tmp_prev)
			tmp_prev->prev = redir;
		tmp_prev = redir;
		redir->order = n + 1;
		redir->next = tmp_next;
		tmp_next = redir;
		redir->str = NULL;
		redir->type = 0;
		redir->fd = 0;
	}
	redir->prev = NULL;
	return (redir);
}
