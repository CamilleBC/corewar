/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 22:12:41 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/16 11:18:49 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <ncurses.h>

# define ARENA_WIDTH		197
# define STATS_WIDTH		48
# define ARENA_HEIGHT		68
# define COLOR_WHITEPLUS	9
# define HEADER_WIDTH		(ARENA_WIDTH + STATS_WIDTH)
# define HEADER_HEIGHT		7
# define HEADER_LINE_1		"   ______                                  "
# define HEADER_LINE_2		"  / ____/___  ________ _      ______ ______"
# define HEADER_LINE_3		" / /   / __ \\/ ___/ _ \\ | /| / / __ `/ ___/"
# define HEADER_LINE_4		"/ /___/ /_/ / /  /  __/ |/ |/ / /_/ / /    "
# define HEADER_LINE_5		"\\____/\\____/_/   \\___/|__/|__/\\__,_/_/     "

struct	s_vm;

typedef struct	s_win
{
	WINDOW	*arena_win;
	WINDOW	*header_win;
	WINDOW	*stats_win;
}				t_win;
WINDOW	*create_newwin(int height, int width, int starty, int startx);
void	free_visu(struct s_vm *vm);
void	init_visu(struct s_vm *vm);
void	print_arena(struct s_vm *vm);
void	print_header(struct s_vm *vm);
void	print_stats(struct s_vm *vm);

#endif
