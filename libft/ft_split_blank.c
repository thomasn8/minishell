/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_blank.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:44:55 by tnanchen          #+#    #+#             */
/*   Updated: 2022/01/27 21:15:48 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// like ft_split but split between space and tab && until \n or \0
static int	words_count(const char *str)
{
	int	i;
	int	switcher;

	i = 0;
	switcher = 0;
	while (*str && *str != '\n')
	{
		if (*str != ' ' && *str != '\t' && switcher == 0)
		{
			switcher = 1;
			i++;
		}
		else if (*str == ' ' || *str == '\t')
			switcher = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int word_n, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	if (start == end && !word_n)
		return (NULL);
	word = malloc((end - start + 1) * sizeof(char));
	while (start < end)
		word[i++] = str[start++];
	word[i] = 0;
	return (word);
}

static char	**words_split(char **tab, char const *s)
{
	int	i;
	int	start;
	int	end;
	int	word;

	i = 0;
	start = 0;
	end = 0;
	word = 0;
	while (s[i] && s[i] != '\n')
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		start = i;
		while (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i])
			i++;
		end = i;
		if ((s[i] == '\n' || !s[i]) && start == end && word > 0)
			return (tab);
		tab[word] = word_dup(s, word, start, end);
		word++;
	}
	return (tab);
}

char	**ft_split_blank(char const *s)
{
	char	**tab;
	size_t	words;

	if (!s)
		return (0);
	words = words_count(s);
	tab = malloc((words + 1) * sizeof(char *));
	if (!tab)
		return (0);
	if (!(words_split(tab, s)))
	{
		free(tab);
		return (NULL);
	}
	tab[words] = NULL;
	return (tab);
}
