/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 11:00:49 by tgunzbur          #+#    #+#             */
/*   Updated: 2018/04/12 14:26:01 by tgunzbur         ###   ########.fr       */
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
		if (++error->line && get_next_line(error->fd, &line) < 0)
			return (NULL);
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
	str[count++] = '\0';
	while (str[count] && str[count] != COMMENT_CHAR)
		if (!ft_isspace(str[count++]))
			return (NULL);
	return (str);
}

int			move_after_token(char *line, t_tok_type tok, int c)
{
	if ((tok == TOK_STR || tok == TOK_USELESS))
	{
		while (line[c] && line[c] != '"')
			c++;
		c += (line[c] ? 1 : 0);
	}
	else if (tok == TOK_LABEL)
		while (line[c] && line[c] != LABEL_CHAR)
			c++;
	else if (tok == TOK_NAME || tok == TOK_COMMENT)
		while (line[c] && !ft_isspace(line[c]) && line[c] != '"')
			c++;
	else
	{
		while (line[c] && !ft_isspace(line[c]) &&
				line[c] != SEP_CHAR && line[c] != COMMENT_CHAR)
			c++;
		if (ft_isspace(line[c]))
			while (line[c] && ft_isspace(line[c]))
				c++;
	}
	return (c);
}

int			go_next_token(char *line, t_tok_type tok, void *data)
{
	int		c;
	char	*op;

	c = 1;
	if (tok == TOK_OP)
	{
		op = get_ops()[*((int *)data) - 1].str;
		while (line[c] && op[c] && line[c] == op[c])
			c++;
	}
	else
		c = move_after_token(line, tok, c);
	if (line[c] == SEP_CHAR || line[c] == LABEL_CHAR)
		c++;
	while (line[c] && ft_isspace(line[c]))
		c++;
	return (c);
}

t_tok		*check_line(t_tok *first_tok, char *line, t_error *error)
{
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
		count += go_next_token(&line[count], token->tok, token->data);
	}
	if (!(token = push_token(token)))
		return (NULL);
	token->tok = TOK_NEWLINE;
	return (token);
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
		if (!line || !(token = check_line(token, line, error)))
			return (super_free(first_tok, line, error->fd));
		free(line);
		error->line++;
	}
	if (!first_tok->next || no_code(first_tok)
		|| !verify_list(first_tok, error))
		return (super_free(first_tok, line, error->fd));
	free(line);
	close(error->fd);
	compile(first_tok);
	return (first_tok);
}
