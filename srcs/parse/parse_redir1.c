/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:55:30 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:55:31 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	input_or_output_list(char r, t_redir *tmp)
{
	char	redir;

	if (r == '<')
		redir = '<';
	else
		redir = '>';
	if (redir == '<')
		(tmp->count_in)++;
	if (redir == '>')
		(tmp->count_out)++;
	return (redir);
}

static void	parse_move_index(t_redir *tmp, int type, int *len, int *start)
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
}

static void	parse_redir_list(char *str, int *i, t_redir *tmp)
{
	int		len;
	int		start;
	char	redir;

	len = 0;
	tmp->str = str;
	redir = input_or_output_list(str[*i], tmp);
	start = *i + 1;
	if (str[*i + 1] == redir)
		parse_move_index(tmp, 2, &len, &start);
	else
		parse_move_index(tmp, 1, &len, &start);
	*i = start + len;
}

void	redir_list_create(char *str, t_redir *tmp, t_cmd *cmd)
{
	int		i;
	char	quote;

	i = 0;
	quote = '0';
	tmp->count_in = 0;
	tmp->count_out = 0;
	while (str[i])
	{
		quotes(str[i], &quote);
		if (quote == '0' && (str[i] == '<' || str[i] == '>'))
		{
			tmp->quote = quote;
			parse_redir_list(str, &i, tmp);
		}
		else
			i++;
	}
	if (tmp->count_in > 0)
		cmd->first_in_redir = io_list_create(tmp->count_in);
	if (tmp->count_out > 0)
		cmd->first_out_redir = io_list_create(tmp->count_out);
}
