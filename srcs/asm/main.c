/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 11:00:49 by tgunzbur          #+#    #+#             */
/*   Updated: 2018/03/26 11:51:59 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			main(int argc, char **argv)
{
	t_error error;
	t_tok	*tmp;

	if (argc != 2)
		return (0);
	error.line = 1;
	if (!(tmp = check_file(argv[1], &error)))
		ft_print("Error at line [%d]\n", error.line);
	else
		super_free(tmp, NULL, -1);
	return (0);
}
