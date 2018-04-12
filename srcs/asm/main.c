/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 11:00:49 by tgunzbur          #+#    #+#             */
/*   Updated: 2018/04/12 12:33:53 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			no_code(t_tok *first_tok)
{
	t_tok	*token;

	token = first_tok->next;
	while (token)
	{
		if (token->tok == TOK_OP || token->tok == TOK_LABEL)
			return (0);
		token = token->next;
	}
	return (1);
}

int			check_extension(char *file)
{
	int	count;

	count = ft_strlen(file);
	if (file[count - 1] != 's' || file[count - 2] != '.')
		return (0);
	return (1);
}

int			main(int argc, char **argv)
{
	t_error error;
	t_tok	*tmp;
	int		count;

	count = 1;
	if (argc == 1)
		ft_print("usage: ./asm [file.s]\n");
	while (count < argc)
	{
		error.line = 1;
		if (!check_extension(argv[count]))
			ft_print("File n%d not valid\n", count);
		else if (!(tmp = check_file(argv[count], &error)))
			ft_print("Error in File n%d at line [%d]\n", count, error.line);
		else
			super_free(tmp, NULL, -1);
		count++;
	}
	return (0);
}
