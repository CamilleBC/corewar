/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:57:24 by briviere          #+#    #+#             */
/*   Updated: 2018/03/19 09:22:54 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_or(const t_instr_fn_args *args)
{
	//uint32_t	res;

	if (args->nb_args != 3)
	{
		args->proc->carry = 0;
		return ;
	}
	// TODO:
}