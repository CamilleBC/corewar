/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 22:12:41 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/14 18:45:07 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <ncurses.h>

struct	s_vm;

WINDOW	*create_newwin(int height, int width, int starty, int startx);
void	destroy_visu(void);
void	init_visu(struct s_vm *vm);
void	print_arena(struct s_vm *vm);

#endif
