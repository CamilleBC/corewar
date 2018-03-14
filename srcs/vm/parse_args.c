/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:17:37 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/14 16:23:20 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int32_t	parse_args(t_vm *vm, int ac, char **av)
{
	int32_t	i;
	(void)ac;

	i = 1;
	while (av[i])
	{
		if (ft_strequ(av[i], "--visual") || ft_strequ(av[i], "-v"))
			vm->flags |= (1 << VISUAL);
		else if (ft_strequ(av[i], "--dump") || ft_strequ(av[i], "-d"))
		{
			if (av[i + 1])
				vm->dump = ft_atoi64(av[++i]);
			if (vm->dump <= INT32_MAX && vm->dump > 0)
				vm->flags |= (1 << DUMP);
		}
		else
			break;
		++i;
	}
	return (i);
}
