/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:42:42 by briviere          #+#    #+#             */
/*   Updated: 2018/04/12 13:03:51 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

void		write_arena(t_arena_args args, uint32_t val, int colour)
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

uint32_t	read_arena(t_arena_args args)
{
	return (array_to_int_arena(args.arena + args.idx, args.len));
}
