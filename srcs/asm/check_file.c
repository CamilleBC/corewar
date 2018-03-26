/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 11:00:49 by tgunzbur          #+#    #+#             */
/*   Updated: 2018/03/26 12:37:51 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*copy_str(char *line, t_error *error)
{
	char	*str;
	char	*tmp;
	int		count;

	str = ft_strdup(line);
	while (!ft_strchr(str, '"'))
	{
		if (get_next_line(error->fd, &line) < 0)
			return (NULL);
		error->line++;
		tmp = str;
		str = ft_strjoin(tmp, "\n");
		free(tmp);
		tmp = str;
		str = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
	}
	count = 0;
	while (str[count] != '"')
		count++;
	str[count] = '\0';
	return (str);
}

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
		while (line[c] && !ft_isspace(line[c]) &&
				line[c] != SEP_CHAR && line[c] != COMMENT_CHAR)
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

t_tok		*check_line(t_tok *first_tok, char *line, t_error *error)
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
				!get_data(&line[count], token->tok, &(token->data), error))
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
	char	*line;
	t_tok	*first_tok;
	t_tok	*token;

	first_tok = NULL;
	if (!(first_tok = push_token(first_tok)))
		return (NULL);
	first_tok->data = (void *)ft_strsub(file, 0, ft_strlen(file) - 2);
	token = first_tok;
	if ((error->fd = open(file, O_RDONLY)) < 0)
		return (super_free(first_tok, NULL, error->fd));
	while (get_next_line(error->fd, &line) > 0)
	{
		error->line++;
		if (!line || !(token = check_line(token, line, error)))
			return (super_free(first_tok, line, error->fd));
		free(line);
	}
	if (!first_tok->next || !verify_list(first_tok, error))
		return (super_free(first_tok, line, error->fd));
	free(line);
	close(error->fd);
	compile(first_tok);
	return (first_tok);
}
