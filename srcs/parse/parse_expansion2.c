/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansion2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:55:21 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/21 17:55:22 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*remove_quote(char *component, int *i)
{
	char	*tmp;

	tmp = component;
	component = ft_cut_strnstr(component, *i, 1);
	free(tmp);
	return (component);
}

static char	*get_exit_status(char *component, int *i, int *status)
{
	int		start;
	char	*value;
	char	*tmp;

	start = *i + 1;
	value = ft_itoa(*status);
	tmp = component;
	component = ft_replace_strnstr(component, value, start - 1, 2);
	free(tmp);
	if (value)
		*i = start + ft_strlen(value) - 1;
	else
		*i = start - 1;
	free(value);
	return (component);
}

static char	*replace_env(char *component, int *i)
{
	int		start;
	int		len;
	char	*key;
	char	*value;
	char	*tmp;

	start = *i + 1;
	len = 0;
	while (ft_notblank(component[start + len]) && component[start + len] != '\"'\
			&& component[start + len] != '\'' && component[start + len] != '$')
		len++;
	key = ft_substr(component, start, len);
	value = get_minishell_env(key);
	tmp = component;
	component = ft_replace_strnstr(component, value, start - 1, len + 1);
	if (value)
		*i = start + ft_strlen(value) - 1;
	else
		*i = start - 1;
	free(key);
	free(tmp);
	free(value);
	return (component);
}

char	*expansion_component(char *compo, int *status)
{
	int		i;
	char	quote;

	i = 0;
	quote = '0';
	while (compo[i])
	{
		quotes(compo[i], &quote);
		if ((quote == '0' && (compo[i] == '\"' || compo[i] == '\'')) \
			|| (quote == '\"' && compo[i] == '\"') \
			|| (quote == '\'' && compo[i] == '\''))
			compo = remove_quote(compo, &i);
		else if (compo[i] == '$' && \
				compo[i + 1] == '?' && quote != '\'')
			compo = get_exit_status(compo, &i, status);
		else if (compo[i] == '$' && quote != '\'' && ft_notblank(compo[i + 1]))
			compo = replace_env(compo, &i);
		else
			i++;
	}
	return (compo);
}
