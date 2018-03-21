/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 13:25:52 by briviere          #+#    #+#             */
/*   Updated: 2018/03/20 13:28:41 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_instr_def	g_instr_tab[OP_COUNT] =
{
	{1, instr_live},
	{2, instr_ld},
	{3, instr_st},
	{4, instr_add},
	{5, instr_sub},
	{6, instr_and},
	{7, instr_or},
	{8, instr_xor},
	{9, instr_zjmp},
	{10, instr_ldi},
	{11, instr_sti},
	{12, instr_fork},
	{13, instr_lld},
	{14, instr_lldi},
	{15, instr_lfork},
	{16, instr_aff},
};

t_instr_fn		*get_instr_fn(int opcode)
{
	size_t	idx;

	idx = 0;
	while (idx < OP_COUNT)
	{
		if (g_instr_tab[idx].opcode == opcode)
			return (g_instr_tab[idx].fn);
		idx++;
	}
	return (0);
}
