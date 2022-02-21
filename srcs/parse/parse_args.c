/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:55:11 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:55:12 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	split_args_list(t_args *tmp2, t_cmd *cmd)
{
	if (tmp2->args_list)
	{
		cmd->args = ft_split(tmp2->args_list, '\n');
		free(tmp2->args_list);
		tmp2->args_list = NULL;
	}
}

static void	*put_arg_in_cmd(char *arg, t_args *tmp2, t_cmd *cmd)
{
	static char	*args_list;
	char		*tmp_list;

	if (tmp2->args_count == 1)
	{
		args_list = NULL;
		cmd->name = arg;
		if (!args_list)
			args_list = ft_strdup("");
		tmp_list = ft_strjoin(args_list, arg);
		free(args_list);
		args_list = tmp_list;
		tmp2->args_list = args_list;
	}
	if (tmp2->args_count > 1)
	{
		tmp_list = ft_strjoin_3(args_list, "\n", arg);
		free(arg);
		free(args_list);
		args_list = tmp_list;
		tmp2->args_list = args_list;
	}
	return (NULL);
}

void	parse_args(char *str, int *i, t_args *tmp2, t_cmd *cmd)
{
	int		len;
	int		start;
	char	*arg;

	tmp2->args_count++;
	len = 0;
	start = *i;
	while (notblank_quotes(str[start + len]))
	{
		if (tmp2->quote == '0' && \
			(str[start + len] == '<' || str[start + len] == '>'))
			break ;
		len++;
	}
	arg = ft_substr(str, start, len);
	if (arg && !arg[0])
		free(arg);
	if (arg)
		put_arg_in_cmd(arg, tmp2, cmd);
	*i = start + len;
}
