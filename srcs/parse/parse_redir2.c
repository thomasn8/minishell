/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:55:47 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:55:48 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	input_or_output(char r, int *order_in, int *order_out)
{
	char	redir;

	if (r == '<')
		redir = '<';
	else
		redir = '>';
	if (redir == '<')
		(*order_in)++;
	if (redir == '>')
		(*order_out)++;
	return (redir);
}

static char	*parse_filename_or_limiter(t_redir *tmp, int type, \
										int *len, int *start)
{
	int		i;
	char	quote;

	i = *start - 1;
	if (type == 2)
		(*start)++;
	if (!ft_notblank(tmp->str[i + type]))
	{
		while (!ft_notblank(tmp->str[i + type + *len]))
			(*len)++;
		*start = i + type + *len;
		*len = 0;
	}
	quote = '0';
	while (notblank_quotes(tmp->str[*start + *len]))
	{
		quotes(tmp->str[*start + *len], &quote);
		if (quote == '0' && tmp->quote == '0' && (tmp->str[*start + *len] == '<'\
			|| tmp->str[*start + *len] == '>'))
			break ;
		(*len)++;
	}
	return (ft_substr(tmp->str, *start, *len));
}

static void	simple_or_double(t_redir *tmp, int i, int *len, int *start)
{
	if (tmp->str[i + 1] == tmp->redir)
	{
		tmp->file_or_limiter = parse_filename_or_limiter(tmp, 2, len, start);
		tmp->type = 2;
	}
	else
	{
		tmp->file_or_limiter = parse_filename_or_limiter(tmp, 1, len, start);
		tmp->type = 1;
	}
}

static void	put_redir_in_cmd(t_cmd *cmd, t_redir *tmp, char redir)
{
	static t_ioredir	*in_current;
	static t_ioredir	*out_current;

	if (redir == '<')
	{
		if (tmp->order_in == 1)
			in_current = cmd->first_in_redir;
		in_current->str = tmp->file_or_limiter;
		in_current->type = tmp->type;
		in_current = in_current->next;
	}
	if (redir == '>')
	{
		if (tmp->order_out == 1)
			out_current = cmd->first_out_redir;
		out_current->str = tmp->file_or_limiter;
		out_current->type = tmp->type;
		out_current = out_current->next;
	}
}

void	parse_redir(char *str, int *i, t_redir *tmp, t_cmd *cmd)
{
	int		len;
	int		start;

	tmp->str = str;
	len = 0;
	tmp->redir = input_or_output(str[*i], &tmp->order_in, &tmp->order_out);
	start = *i + 1;
	simple_or_double(tmp, *i, &len, &start);
	put_redir_in_cmd(cmd, tmp, tmp->redir);
	*i = start + len;
}
