/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 14:11:32 by briviere          #+#    #+#             */
/*   Updated: 2018/04/12 14:32:11 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		dump_arena(const t_arena arena[MEM_SIZE])
{
	size_t		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (!(i % 0x40))
		{
			if (i != 0)
				ft_putchar('\n');
			ft_putstr("0x");
			print_hex(i / 256);
			print_hex(i % 256);
			ft_putstr(" : ");
		}
		print_hex(arena[i].hex);
		ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}
