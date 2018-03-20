/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:58:53 by briviere          #+#    #+#             */
/*   Updated: 2018/03/20 09:59:28 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_aff(const t_instr_fn_args *args)
{
	if (args->vm->flags & (1 << VISUAL) || args->op->nb_args != args->nb_args)
		return ;
}
