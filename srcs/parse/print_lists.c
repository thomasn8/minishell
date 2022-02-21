/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:56:14 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:56:15 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_io_redir(t_ioredir *redir, char *i_or_o)
{
	t_ioredir	*current;

	current = redir;
	while (current->next != NULL)
	{
		printf("%s%s redir #%d: | type: %d | file/limiter: %s |%s\n", BLU, \
				i_or_o, current->order, current->type, current->str, WHI);
		current = current->next;
	}
	printf("%s%s redir #%d: | type: %d | file/limiter: %s |%s\n", BLU, \
			i_or_o, current->order, current->type, current->str, WHI);
}

static void	print_cmd_list(t_cmd *cmd)
{
	int	i;

	i = 0;
	printf("%sCmd #%d (%p - next is %p - prev is %p)%s\n", CYA, \
			cmd->order, cmd, cmd->next, cmd->prev, BLU);
	printf("%sName: %s | Args (%p): %s", BLU, cmd->name, cmd->args, WHI);
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			printf("%s%s (%p); %s", BLU, cmd->args[i], cmd->args[i], WHI);
			i++;
		}
	}
	printf("\n");
	if (cmd->first_in_redir != NULL)
		print_io_redir(cmd->first_in_redir, "_Input");
	if (cmd->first_out_redir != NULL)
		print_io_redir(cmd->first_out_redir, "Output");
}

void	print_all(t_cmd *first_cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	if (first_cmd)
	{
		current = first_cmd;
		while (current)
		{
			next = current->next;
			print_cmd_list(current);
			current = next;
		}
		printf("%s", WHI);
	}
}
