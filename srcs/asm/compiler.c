/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaydont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:17:47 by chaydont          #+#    #+#             */
/*   Updated: 2018/03/20 09:58:15 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Lit les prochains arguments en renvois le param_code correspondant
*/

static int	get_param_code(t_tok *file, int nb)
{
	int param_code;
	int i;

	param_code = 0;
	i = 3 - nb;
	nb = 3;
	while (nb > i)
	{
		if (file->tok == TOK_REG)
			param_code += REG_CODE << nb * 2;
		else if (file->tok == TOK_DIR_LB || file->tok == TOK_DIR_NB)
			param_code += DIR_CODE << nb * 2;
		else if (file->tok == TOK_INDIR_LB || file->tok == TOK_INDIR_NB)
			param_code += IND_CODE << nb * 2;
		file = file->next;
		nb--;
	}
	return (param_code);
}

/*
** Ecrit l'operation et ses arguments dans le fichier binaire.
*/

static void	write_op(t_tok *file, t_tok *first_nod, int cursor, int fd)
{
	int		*op;
	int		nb_arg;
	int		arg;
	t_op	*op_tab;

	op_tab = get_ops();
	op = (int*)file->data;
	nb_arg = op_tab[*op - 1].nb_args;
	ft_putchar_fd(*op, fd);
	if (op_tab[*op - 1].octal)
		ft_putchar_fd(get_param_code(file->next, nb_arg), fd);
	while (nb_arg-- >= 1)
	{
		if ((file = file->next)->tok == TOK_INDIR_LB || file->tok == TOK_DIR_LB)
			arg = get_label_pos(first_nod, file->data) - cursor;
		else
			arg = *(int *)file->data;
		if (file->tok == TOK_REG)
			ft_putchar_fd((char)arg, fd);
		else if (file->tok == TOK_INDIR_NB || file->tok == TOK_INDIR_LB ||
				op_tab[*op - 1].dir_size)
			ft_putshort_fd((short)arg, fd);
		else if (file->tok == TOK_DIR_NB || file->tok == TOK_DIR_LB)
			ft_putint_fd(arg, fd);
	}
}

static void	write_file(t_tok *file, int fd)
{
	int		cursor;
	t_tok	*first_nod;

	first_nod = file;
	cursor = 0;
	while (file)
	{
		if (file->tok == TOK_OP)
		{
			write_op(file, first_nod, cursor, fd);
			cursor += get_op_length(file);
		}
		file = file->next;
	}
}

int			compile(t_tok *file)
{
	int			fd;
	char		*file_name;
	t_header	header;

	file_name = ft_strjoin(file->data, ".cor");
	file = file->next;
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	header = get_header(file);
	write_header(header, fd);
	write_file(file, fd);
	close(fd);
	ft_print("Writing output program to %s\n", file_name);
	free(file_name);
	return (1);
}
