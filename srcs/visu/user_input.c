/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 15:00:51 by cbaillat          #+#    #+#             */
/*   Updated: 2018/04/11 10:26:43 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visu.h"

int8_t	init_user_input(void)
{
	if (nodelay(stdscr, 1) == ERR
		|| cbreak() == ERR
		|| keypad(stdscr, TRUE) == ERR
		|| define_key(" ", KEY_SPACE) == ERR)
		return (ERROR);
	return (SUCCESS);
}

int		get_number(int key, int old_cycles)
{
	int		cycles;
	int		i;
	char	number[33];

	i = 0;
	cycles = old_cycles;
	ft_bzero((void*)number, sizeof(char) * 33);
	while (ft_isdigit(key))
	{
		number[i++] = key;
		if (i >= 32)
			break ;
		while ((key = getch()) == ERR)
			;
	}
	number[i] = '\0';
	if (key == KEY_RIGHT || key == KEY_SPACE || key == KEY_ETR)
		cycles = ft_atoi(number);
	return (cycles);
}

int		manage_user_input(uint8_t *run, int old_cycles)
{
	int		cycles;
	int		key;

	cycles = old_cycles;
	if ((key = getch()) != ERR)
	{
		if ((key == KEY_SPACE || key == KEY_ETR) && *run == 0)
			*run = 1;
		else if (key == KEY_SPACE || key == KEY_ETR)
			*run = 0;
		else if (key == KEY_RIGHT)
			cycles = 1;
		else
			cycles = get_number(key, old_cycles);
	}
	return (cycles);
}
