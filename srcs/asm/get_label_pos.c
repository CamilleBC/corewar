/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_label_position.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaydont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 15:53:42 by chaydont          #+#    #+#             */
/*   Updated: 2018/03/16 12:58:53 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int g_arg[16] = {1, 2, 2, 3, 3, 3, 3, 3, 1, 3, 3, 1, 2, 3, 1, 1};

/*
** Renvois la longueur en octet d'une operation
*/

int			get_op_length(t_tok *file)
{
	int i;
	int nb_arg;
	int *op;

	i = 1;
	op = file->data;
	nb_arg = g_arg[*op - 1];
	if (nb_arg != 1 || *op == 16)
		i++;
	while (nb_arg-- >= 1)
	{
		file = file->next;
		if (file->tok == TOK_REG)
			i += 1;
		else if ((file->tok == TOK_DIR_NB || file->tok == TOK_DIR_LB) &&
				!(*op == 10 || *op == 11 || *op == 14 || *op == 9))
			i += 4;
		else
			i += 2;
	}
	return (i);
}

/*
** Recupere la position d'un label en octet.
** Si le nom du label est \0, renvois la longueur
** totale du programe.
*/

int			get_label_pos(t_tok *file, char *label)
{
	int		i;

	i = 0;
	while (file)
	{
		if (file->tok == TOK_OP)
			i += get_op_length(file);
		else if (file->tok == TOK_LABEL && !ft_strcmp(label, file->data))
			return (i);
		file = file->next;
	}
	return (i);
}

/*
** Recupere toute les informations contenues dans le header
*/

t_header	get_header(t_tok *file)
{
	t_header	header;
	t_tok		*first_nod;

	ft_bzero(header.prog_name, PROG_NAME_LENGTH + 4);
	ft_bzero(header.comment, COMMENT_LENGTH + 4);
	header.magic = COREWAR_EXEC_MAGIC;
	if (file->tok == TOK_NAME)
		ft_strcpy(header.prog_name, (file = file->next)->data);
	else if (file->tok == TOK_COMMENT)
		ft_strcpy(header.comment, (file = file->next)->data);
	if ((file = file->next->next)->tok == TOK_NAME)
		ft_strcpy(header.prog_name, (file = file->next)->data);
	else if (file->tok == TOK_COMMENT)
		ft_strcpy(header.comment, (file = file->next)->data);
	first_nod = file->next;
	header.prog_size = get_label_pos(file->next, "");
	file = first_nod;
	return (header);
}
