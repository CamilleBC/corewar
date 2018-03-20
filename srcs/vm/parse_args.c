/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:17:37 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/20 12:31:40 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int32_t	parse_args(t_vm *vm, int ac, char **av)
{
	int32_t	i;

	i = 1;
	while (i < ac)
	{
		if (ft_strequ(av[i], "--ncurses") || ft_strequ(av[i], "-n"))
			vm->flags |= (1 << VISUAL);
		else if (ft_strequ(av[i], "--dump") || ft_strequ(av[i], "-d"))
		{
			if (av[i + 1])
				vm->dump = ft_atoi64(av[++i]);
			if (vm->dump <= INT32_MAX && vm->dump > 0)
				vm->flags |= (1 << DUMP);
		}
		else if (ft_strequ(av[i], "--verbose") || ft_strequ(av[i], "-v"))
		{
			if (av[i + 1] && ft_strisnum(av[i + 1]))
				vm->verbose = ft_atoi(av[++i]);
			else
				vm->verbose = 1;
		}
		else
			break;
		++i;
	}
	return (i);
}
