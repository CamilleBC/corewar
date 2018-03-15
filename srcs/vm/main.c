/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 19:50:22 by briviere          #+#    #+#             */
/*   Updated: 2018/03/15 17:45:17 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

int		main(int ac, char **av)
{
	int32_t	i;
	t_vm	*vm;

	if (!(vm = init_vm()))
		return (0);
	parse_args(vm, ac, av);
	if (vm->flags & (1 << VISUAL))
		init_visu(vm);
	i = -1;
	if (vm->flags & (1 << VISUAL))
	{
		print_arena(vm);
		print_header(vm);
		print_stats(vm);
	}
	touchwin(vm->arena_win);
	touchwin(vm->stats_win);
	while (1)
		;
	while (++i < vm->nb_players)
		ft_print("Player #%d: %s\n", i, vm->players[i]->name);
	if (vm->flags & (1 << VISUAL))
		free_visu(vm);
	return (0);
}
