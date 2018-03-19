/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:27:49 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/16 13:55:11 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "vm.h"

WINDOW	*create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *win;

	win = newwin(height, width, starty, startx);
	return win;
}
