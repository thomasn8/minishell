/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:55:52 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:55:53 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_pipes(char *cmd)
{
	int		i;
	int		pipes;
	char	quote;

	i = 0;
	pipes = 0;
	quote = '0';
	while (cmd[i] != '\0')
	{
		quotes(cmd[i], &quote);
		if (quote == '0' && cmd[i] == '|')
			pipes++;
		if (quote == '0' && ((cmd[i] == '>' && cmd[i + 1] == '<') || \
			(cmd[i] == '<' && cmd[i + 1] == '>')))
			return (-1);
		i++;
	}
	return (pipes);
}

static int	syntax_error(int pipes, char *cmd, char **cmd_split)
{
	free(cmd);
	ft_free_arr(cmd_split);
	if (pipes == -1)
		ft_putendl_fd("minishell: syntax error near unexpected token `<'", 2);
	else
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
	return (-1);
}

int	parse_syntax(char *cmd, char **cmd_split)
{
	int	i;
	int	j;
	int	cmds;
	int	pipes;

	i = 0;
	cmds = 0;
	pipes = count_pipes(cmd);
	while (cmd_split[i])
	{
		j = 0;
		while (cmd_split[i][j] != '\0')
		{
			if (ft_notblank(cmd_split[i][j]))
			{
				cmds++;
				break ;
			}
			j++;
		}
		i++;
	}
	if ((pipes && pipes >= cmds) || pipes == -1)
		return (syntax_error(pipes, cmd, cmd_split));
	return (cmds);
}
