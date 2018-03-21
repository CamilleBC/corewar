/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 09:03:05 by briviere          #+#    #+#             */
/*   Updated: 2018/03/19 09:06:42 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

inline int8_t	is_valid_reg(uint8_t reg)
{
	return (reg >= 1 && reg <= REG_NUMBER);
}

inline int8_t	are_valid_regs(uint8_t *regs, size_t size)
{
	while (size--)
		if (!is_valid_reg(regs[size]))
			return (0);
	return (1);
}
