/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:44:54 by tgunzbur          #+#    #+#             */
/*   Updated: 2018/04/11 15:45:56 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	*super_free(t_tok *first_tok, char *line, int fd)
{
	t_tok	*tmp;

	if (line)
		free(line);
	while (first_tok)
	{
		if (first_tok->data)
			free(first_tok->data);
		tmp = first_tok;
		first_tok = first_tok->next;
		free(tmp);
	}
	if (fd > 0)
		close(fd);
	return (NULL);
}
