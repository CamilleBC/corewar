/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:03:32 by briviere          #+#    #+#             */
/*   Updated: 2018/03/15 16:11:53 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

uint32_t	array_to_int(uint8_t arr[4], size_t size)
{
	uint32_t	val;
	size_t		i;

	if (size > 4)
		return (0);
	val = 0;
	i = 0;
	while (i < size)
	{
		val <<= 8;
		val |= arr[i];
		i++;
	}
	return (val);
}

void		int_to_array(uint8_t arr[4], uint32_t val, size_t size)
{
	if (size > 4)
		return ;
	while (size--)
		arr[3 - size] = val >> size & 0xff;
}
