/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:44:55 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/15 13:05:02 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static int	quotes(char a, char *quote)
{
	if (*quote == '0' && (a == '\'' || a == '\"'))
		*quote = a;
	else if (*quote != '0' && a == *quote)
		*quote = '0';
	return (1);
}

static int	words_count(const char *str, char c)
{
	int		i;
	int		limiter;
	char	quote;

	i = 0;
	limiter = 0;
	quote = '0';
	while (*str)
	{
		quotes(*str, &quote);
		if (*str != c && limiter == 0)
		{
			limiter = 1;
			i++;
		}
		else if (*str == c && quote == '0'
			&& *(str - 1) != '>' && *(str - 1) != '<')
			limiter = 0;
		str++;
	}
	return (i);
}

static char	**words_split(char **tab, char const *s, char c)
{
	t_split_quotes	t;

	t.i = 0;
	t.start = 0;
	t.end = 0;
	t.word = 0;
	t.quote = '0';
	while (s[t.i])
	{
		while (s[t.i] == c && quotes(s[t.i], &t.quote) && t.quote == '0')
			t.i++;
		t.start = t.i;
		while (s[t.i] && ((s[t.i] != c && quotes(s[t.i], &t.quote))
				|| t.quote != '0' || s[t.i - 1] == '>' || s[t.i - 1] == '<'))
			t.i++;
		t.end = t.i;
		if (!s[t.i] && t.start == t.end && t.word > 0)
			return (tab);
		tab[t.word] = word_dup(s, t.word, t.start, t.end);
		t.word++;
	}
	return (tab);
}

char	**ft_split_quotes(char const *s, char c)
{
	char	**tab;
	size_t	words;

	if (!s)
		return (0);
	words = words_count(s, c);
	tab = malloc((words + 1) * sizeof(char *));
	if (!tab)
		return (0);
	if (!(words_split(tab, s, c)))
	{
		free(tab);
		return (NULL);
	}
	tab[words] = NULL;
	return (tab);
}
