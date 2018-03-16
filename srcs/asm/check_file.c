/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 11:00:49 by tgunzbur          #+#    #+#             */
/*   Updated: 2018/03/16 13:20:16 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			go_next_token(char *line, t_tok_type tok)
{
	int		c;

	c = 1;
	if (tok == TOK_STR || tok == TOK_USELESS)
	{
		while (line[c] && line[c] != '"')
			c++;
		if (line[c])
			c++;
	}
	else
	{
		while (line[c] && !ft_isspace(line[c]) && line[c] != SEP_CHAR)
			c++;
		while (line[c] && ft_isspace(line[c]))
			c++;
	}
	if (line[c] == SEP_CHAR)
		c++;
	while (ft_isspace(line[c]))
		c++;
	return (c);
}

t_tok		*check_line(t_tok *first_tok, char *line)
{
	static int	i = 0;
	int			count;
	t_tok		*token;

	token = first_tok;
	count = 0;
	while (ft_isspace(line[count]))
		count++;
	while (line[count])
	{
		if (!(token = push_token(token)) ||
			((token->tok = get_token(&line[count])) == TOK_UNDEFINED) ||
			!get_data(&line[count], token->tok, &(token->data)))
			return (NULL);
		count += go_next_token(&line[count], token->tok);
		i++;
	}
	if (!(token = push_token(token)))
		return (NULL);
	token->tok = TOK_NEWLINE;
	return (token);
}

void		*super_free(t_tok *first_tok, char *line, int fd)
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

t_tok		*check_file(char *file, t_error *error)
{
	int		fd;
	char	*line;
	t_tok	*first_tok;
	t_tok	*token;

	first_tok = NULL;
	if (!(first_tok = push_token(first_tok)))
		return (NULL);
	first_tok->data = (void *)ft_strsub(file, 0, ft_strlen(file) - 2);
	token = first_tok;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (super_free(first_tok, NULL, fd));
	error->line++;
	while (get_next_line(fd, &line) > 0)
	{
		if (!(token = check_line(token, line)))
			return (super_free(first_tok, line, fd));
		free(line);
		error->line++;
	}
	if (!verify_list(first_tok))
		return (super_free(first_tok, NULL, fd));
	close(fd);
	compile(first_tok);
	return (first_tok);
}
