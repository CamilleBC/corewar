/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:42:42 by briviere          #+#    #+#             */
/*   Updated: 2018/04/11 10:18:27 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

void	write_arena(t_arena *arena, uint32_t val, size_t idx, size_t len,
		int colour)
{
	uint8_t		new_val[len];
	size_t		i;

	int_to_array(new_val, val, len);
	i = 0;
	while (i < len)
	{
		arena[(idx + i) % MEM_SIZE].hex = new_val[i];
		arena[(idx + i) % MEM_SIZE].new_value = 5;
		arena[(idx + i) % MEM_SIZE].colour = colour;
		i++;
	}
}

uint32_t	read_arena(t_arena *arena, size_t idx, size_t len)
{
	return (array_to_int_arena(arena + idx, len));
}
