/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaydont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 14:57:25 by chaydont          #+#    #+#             */
/*   Updated: 2018/03/16 12:58:46 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_putint_fd(int n, int fd)
{
	ft_putchar_fd((n >> 24) & 0xff, fd);
	ft_putchar_fd((n >> 16) & 0xff, fd);
	ft_putchar_fd((n >> 8) & 0xff, fd);
	ft_putchar_fd(n & 0xff, fd);
}

void	ft_putshort_fd(short n, int fd)
{
	ft_putchar_fd((n >> 8) & 0xff, fd);
	ft_putchar_fd(n & 0xff, fd);
}
