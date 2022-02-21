/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 23:15:31 by tnanchen          #+#    #+#             */
/*   Updated: 2022/01/28 19:08:46 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_3(char const *s1, char const *s2, char const *s3)
{
	char	*start;
	char	*end;

	if (!s1 || !s2 || !s3)
		return (NULL);
	start = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	if (!start)
		return (NULL);
	end = start;
	while (*s1)
		*end++ = *s1++;
	while (*s2)
		*end++ = *s2++;
	while (*s3)
		*end++ = *s3++;
	*end = 0;
	return (start);
}
