/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 09:19:25 by briviere          #+#    #+#             */
/*   Updated: 2018/03/15 10:10:57 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_live(uint8_t mem[MEM_SIZE], t_player *pl, t_proc *proc,
					t_arg args[MAX_ARGS_NUMBER])
{
	(void)mem;
	(void)proc;
	(void)args;
	pl->live++;
}
