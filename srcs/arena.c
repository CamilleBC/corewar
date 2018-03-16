/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:42:42 by briviere          #+#    #+#             */
/*   Updated: 2018/03/16 17:18:23 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

void	write_arena(t_arena *arena, uint32_t val, size_t idx, size_t len)
{
	uint8_t		new_val[len];
	size_t		i;

	dprintf(2, "%d\n", val);
	int_to_array(new_val, val, len);
	i = 0;
	while (i < len)
	{
		arena[idx + i].hex = new_val[i];
		arena[idx + i].new_value = 5;
		arena[idx + i].colour = 1;
		i++;
	}
}

uint32_t	read_arena(t_arena *arena, size_t idx, size_t len)
{
	return (array_to_int_arena(arena + idx, len));
}
