/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:42:42 by briviere          #+#    #+#             */
/*   Updated: 2018/04/16 10:53:58 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

static void		int_to_array(uint8_t arr[4], uint32_t val, size_t size)
{
	if (size > 4)
		return ;
	while (size--)
		arr[3 - size] = val >> (size * 8) & 0xff;
}

void			write_arena(t_arena_args args, uint32_t val, int colour)
{
	uint8_t		new_val[args.len];
	size_t		i;

	int_to_array(new_val, val, args.len);
	i = 0;
	while (i < args.len)
	{
		args.arena[(args.idx + i) % MEM_SIZE].hex = new_val[i];
		args.arena[(args.idx + i) % MEM_SIZE].new_value = HIGHLIGHT_TIME;
		args.arena[(args.idx + i) % MEM_SIZE].colour = colour;
		i++;
	}
}

uint32_t		read_arena(t_arena_args args)
{
	uint32_t	val;
	size_t		i;

	if (args.len > 4)
		return (0);
	val = 0;
	i = 0;
	while (i < args.len)
	{
		val <<= 8;
		val |= args.arena[(args.idx + i) % MEM_SIZE].hex;
		i++;
	}
	return (val);
}
