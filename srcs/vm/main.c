/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 19:50:22 by briviere          #+#    #+#             */
/*   Updated: 2018/03/15 10:11:58 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
#include <fcntl.h>

void	test_interpret(char *file)
{
	size_t	idx;
	size_t	len;
	int		fd;
	t_player	fake_pl;
	t_proc		fake_proc;


	ft_bzero(&fake_proc, sizeof(t_proc));
	ft_bzero(&fake_pl, sizeof(t_player));
	fd = open(file, O_RDONLY);
	unsigned char	buf[PROG_NAME_LENGTH + COMMENT_LENGTH + 1 + 16];

	// SKIP DESCRIPTION, JUST FOR DEBUG
	ft_print("read %x\n", read(fd, buf, PROG_NAME_LENGTH + COMMENT_LENGTH + 16));
	unsigned int	size = 0;
	for (int i = 0; i < 4; i++) {
		size <<= 8;
		size |= buf[i + PROG_NAME_LENGTH + 8];
		ft_print("%x\n", buf[i + PROG_NAME_LENGTH + 8]);
	}
	ft_print("size %d\n", size);
	if (size > CHAMP_MAX_SIZE)
	{
		ft_print("invalide\n");
		return;
	}
	len = read(fd, fake_pl.instr, CHAMP_MAX_SIZE);
	ft_print("%d %d\n", len, CHAMP_MAX_SIZE);
	idx = 0;
	while (idx < len)
	{
		interpret_instr(fake_pl.instr, &fake_pl, &fake_proc);
		idx++;
	}
	ft_print("lives: %d\n", fake_pl.live);
}

int		main(int ac, char **av)
{
	int32_t	i;
	t_vm	vm;

	parse_args(&vm, ac, av);
	init_vm(&vm);
	i = -1;
	while (++i < vm.nb_players)
		ft_print("Player #%d: %s\n", i, vm.players[i]->name);
	test_interpret(av[1]);
	return (0);
}
