/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:56:10 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:56:11 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	initialize_tmps(t_components *c)
{
	c->i = 0;
	c->quote = '0';
	c->tmp.order_in = 0;
	c->tmp.order_out = 0;
	c->tmp2.args_count = 0;
	c->tmp2.args_list = NULL;
}

static int	parse_components(char	*str, t_cmd *cmd)
{
	t_components	c;

	initialize_tmps(&c);
	redir_list_create(str, &c.tmp, cmd);
	while (str[c.i])
	{
		quotes(str[c.i], &c.quote);
		if (c.quote == '0' && (str[c.i] == '<' || str[c.i] == '>'))
		{
			c.tmp.quote = c.quote;
			parse_redir(str, &c.i, &c.tmp, cmd);
		}
		else if (ft_notblank(str[c.i]))
		{
			c.tmp2.quote = c.quote;
			parse_args(str, &c.i, &c.tmp2, cmd);
			if (c.quote != '0')
				c.quote = '0';
		}
		else
			c.i++;
	}
	split_args_list(&c.tmp2, cmd);
	return (0);
}

static char	*remove_cmd_newline(char *cmd)
{
	char	*tmp;

	tmp = cmd;
	cmd = ft_substr(cmd, 0, ft_strlen(cmd) - 1);
	free(tmp);
	return (cmd);
}

t_cmd	*parsing(char *cmd, int *n, int *status)
{
	char	**cmd_split;
	int		cmd_count;
	t_cmd	*first_cmd;
	t_cmd	*current;
	int		i;

	cmd = remove_cmd_newline(cmd);
	cmd_split = ft_split_quotes(cmd, '|');
	cmd_count = parse_syntax(cmd, cmd_split);
	if (cmd_count < 1)
		return (NULL);
	first_cmd = cmd_list_create(cmd_count);
	i = 0;
	current = first_cmd;
	while (cmd_count--)
	{
		parse_components(cmd_split[i++], current);
		current = current->next;
	}
	expansion(first_cmd, status);
	history(cmd);
	free(cmd);
	ft_free_arr(cmd_split);
	*n = i;
	return (first_cmd);
}
