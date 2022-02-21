/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:55:56 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:55:57 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	notblank_quotes(int c)
{
	static char	quote = '0';

	if (quote == '0' && (c == '\'' || c == '\"'))
		quote = c;
	else if (quote != '0' && c == quote)
		quote = '0';
	if (c == '\0')
		quote = '0';
	if ((c > ' ' && c <= '~') || quote != '0')
		return (1);
	return (0);
}

int	quotes(char a, char *quote)
{
	if (*quote == '0' && (a == '\'' || a == '\"'))
		*quote = a;
	else if (*quote != '0' && a == *quote)
		*quote = '0';
	return (1);
}

void	remove_first(char **tab)
{
	char	*tmp;
	int		i;

	if (tab && tab[0])
	{
		tmp = tab[0];
		i = 0;
		while (tab[i])
		{
			tab[i] = tab[i + 1];
			i++;
		}
		free(tmp);
	}
}
