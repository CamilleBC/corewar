/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 12:50:30 by briviere          #+#    #+#             */
/*   Updated: 2018/03/20 16:02:56 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_hex(char hex)
{
	char	decade;

	decade = hex / 16;
	hex %= 16;
	if (decade >= 10)
		ft_putchar(decade - 10 + 'a');
	else
		ft_putchar(decade + '0');
	if (hex >= 10)
		ft_putchar(hex - 10 + 'a');
	else
		ft_putchar(hex + '0');
}

void		debug_print_pc(uint32_t pc)
{
	ft_putstr("0x");
	print_hex((pc >> 8) & 0xff);
	print_hex(pc & 0xff);
}

void		debug_print_arena(t_arena *arena, uint32_t pc, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		print_hex(arena[pc].hex);
		i++;
		if (i < len)
			ft_putchar(' ');
		pc = (pc + 1) % MEM_SIZE;
	}
}
