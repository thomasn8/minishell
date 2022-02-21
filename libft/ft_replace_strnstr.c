/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_strnstr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:10:06 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/11 14:13:49 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// string string_to_transplant index_start_to_transplant len_of_cut
char	*ft_replace_strnstr(const char *str, const char *graft,
			unsigned int start, unsigned int len)
{
	t_cut	piece;
	int		max_len_of_cut;
	int		len_of_cut;

	max_len_of_cut = ft_strlen(str);
	len_of_cut = start + len;
	if (len_of_cut > max_len_of_cut)
		len_of_cut = max_len_of_cut;
	piece.value = graft;
	piece.before = ft_substr(str, 0, start);
	piece.after = ft_substr(str, start + len, ft_strlen(&str[len_of_cut]));
	if (piece.value)
	{
		piece.new = ft_strjoin_3(piece.before, piece.value, piece.after);
		len = ft_strlen(piece.value);
	}
	else
	{
		piece.new = ft_strjoin(piece.before, piece.after);
		len = 0;
	}
	free(piece.before);
	free(piece.after);
	return (piece.new);
}
