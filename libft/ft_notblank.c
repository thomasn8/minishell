/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_notblank.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:47:32 by tnanchen          #+#    #+#             */
/*   Updated: 2022/01/31 23:18:15 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_notblank(int c)
{
	if (c > ' ' && c <= '~')
		return (1);
	return (0);
}
