/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:17:37 by cbaillat          #+#    #+#             */
/*   Updated: 2018/04/17 14:47:54 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <fcntl.h>

static int	get_id(char **av, int *i)
{
	int	id;

	id = ERROR;
	if (ft_strisnum(av[*i + 1]))
		id = ft_atoi64(av[++(*i)]);
	else
		return (ERROR);
	if (id <= INT16_MAX)
		return (id);
	return (ERROR);
}

static int	get_dump_value(t_vm *vm, char **av, int *i)
{
	if (ft_strisnum(av[*i + 1]))
		vm->dump = ft_atoi64(av[++(*i)]);
	else
		return (ERROR);
	if (vm->dump <= INT32_MAX && vm->dump > 0)
		vm->flags |= (1 << DUMP);
	return (SUCCESS);
}

static int	parse_arg(t_fds *fds, t_vm *vm, char **av, int *i)
{
	static size_t	i_fd;

	if (ft_strequ(av[*i], "--ncurses") || ft_strequ(av[*i], "-nc"))
		vm->flags |= (1 << VISUAL);
	else if (ft_strequ(av[*i], "--number") || ft_strequ(av[*i], "-n"))
	{
		if ((fds[i_fd].id = get_id(av, i)) == ERROR)
			return (ERROR);
	}
	else if (ft_strequ(av[*i], "--dump") || ft_strequ(av[*i], "-d"))
	{
		if (get_dump_value(vm, av, i) == ERROR)
			return (ERROR);
	}
	else if (ft_strequ(av[*i], "--verbose") || ft_strequ(av[*i], "-v"))
		vm->verbose = 1;
	else if ((fds[i_fd++].fd = open(av[*i], O_RDONLY)) < 0)
	{
		ft_putendl_fd("invalid file", 2);
		return (ERROR);
	}
	vm->nb_players = i_fd;
	return (SUCCESS);
}

t_fds		*parse_args(t_vm *vm, int ac, char **av)
{
	int		i;
	t_fds	*fds;

	i = 1;
	if (!(fds = ft_memalloc(sizeof(*fds) * ac)))
		return (NULL);
	while (i < ac)
	{
		if (parse_arg(fds, vm, av, &i) == ERROR)
		{
			free(fds);
			return (NULL);
		}
		++i;
	}
	return (fds);
}
