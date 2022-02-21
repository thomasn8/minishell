/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_strnstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:09:46 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/11 14:14:16 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// string index_start_the_cut len_of_cut
char	*ft_cut_strnstr(const char *str, unsigned int start, unsigned int len)
{
	t_cut	piece;
	int		max_len_of_cut;
	int		len_of_cut;

	max_len_of_cut = ft_strlen(str);
	len_of_cut = start + len;
	if (len_of_cut > max_len_of_cut)
		len_of_cut = max_len_of_cut;
	piece.before = ft_substr(str, 0, start);
	piece.after = ft_substr(str, start + len, ft_strlen(&str[len_of_cut]));
	piece.new = ft_strjoin(piece.before, piece.after);
	free(piece.before);
	free(piece.after);
	return (piece.new);
}
