/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 11:00:49 by tgunzbur          #+#    #+#             */
/*   Updated: 2018/03/15 17:04:52 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "lexer.h"
#include "op.h"

int			is_space(char c)
{
	if (c == ' ' || (c > 7 && c < 13))
		return (1);
	return (0);
}

t_tok		*push_token(t_tok *prev)
{
	t_tok	*new;

	if (prev == NULL)
	{
		if (!(prev = (t_tok *)malloc(sizeof(t_tok))))
			return (NULL);
		prev->tok = TOK_UNDEFINED;
		prev->data = NULL;
		prev->next = NULL;
		return (prev);
	}
	if (!(new = (t_tok *)malloc(sizeof(t_tok))))
		return (NULL);
	new->tok = TOK_UNDEFINED;
	new->data = NULL;
	new->next = NULL;
	prev->next = new;
	return (new);
}

int			is_label(char *line)
{
	int		count;

	count = 0;
	while (line[count] && !is_space(line[count]))
		count++;
	if (line[count - 1] == LABEL_CHAR)
		return (1);
	return (0);
}

int			is_op(char *line)
{
	int count;

	count = 0;
	while (get_ops()[count].str != NULL)
	{
		if (!ft_strncmp(get_ops()[count].str, line,
			ft_strlen(get_ops()[count].str)) &&
			is_space(line[ft_strlen(get_ops()[count].str)]))
			return (count + 1);
		count++;
	}
	return (0);
}

t_tok_type	get_token(char *line)
{
	if (!ft_strncmp(NAME_CMD_STRING, line, 5) && is_space(line[5]))
		return (TOK_NAME);
	if (!ft_strncmp(COMMENT_CMD_STRING, line, 8) && is_space(line[8]))
		return (TOK_COMMENT);
	if (line[0] == COMMENT_CHAR || !line[0] || is_space(line[0]))
		return (TOK_USELESS);
	if (line[0] == DIRECT_CHAR && (ft_isdigit(line[1]) || line[1] == '-'))
		return (TOK_DIR_NB);
	if (line[0] == DIRECT_CHAR && line[1] == LABEL_CHAR)
		return (TOK_DIR_LB);
	if (ft_isdigit(line[0]) || line[0] == '-')
		return (TOK_INDIR_NB);
	if (line[0] == LABEL_CHAR)
		return (TOK_INDIR_LB);
	if (line[0] == '"')
		return (TOK_STR);
	if (is_label(line))
		return (TOK_LABEL);
	if (line[0] == 'r' && ft_isdigit(line[1]))
		return (TOK_REG);
	if (is_op(line))
		return (TOK_OP);
	return (TOK_UNDEFINED);
}

int			*create_int(int i)
{
	int		*nb;

	if (!(nb = (int *)malloc(sizeof(int))))
		return (NULL);
	*nb = i;
	return (nb);
}

char		*first_word(char *line, char c)
{
	int		count;
	char	*str;

	count = 0;
	if (c == '"' || c == LABEL_CHAR)
	{
		while (line[count] != c)
			count++;
		if (!(str = (char *)malloc(sizeof(char) * (count + 1))))
			return (NULL);
		count = -1;
		while (line[++count] != c)
			str[count] = line[count];
		return (str);
	}
	while (line[count] == SEP_CHAR || is_space(line[count]))
		count++;
	if (!(str = (char *)malloc(sizeof(char) * (count + 1))))
		return (NULL);
	count = -1;
	while (line[++count] != SEP_CHAR && !is_space(line[count]))
		str[count] = line[count];
	return (str);
}

int			get_data(char *line, t_tok_type tok, void **data)
{
	if (tok == TOK_DIR_NB || tok == TOK_REG)
		*data = create_int(ft_atoi(&line[1]));
	if (tok == TOK_INDIR_NB)
		*data = create_int(ft_atoi(line));
	if (tok == TOK_OP)
		*data = create_int(is_op(line));
	if (tok == TOK_DIR_LB)
		*data = first_word(&line[2], SEP_CHAR);
	if (tok == TOK_INDIR_LB)
		*data = first_word(&line[1], SEP_CHAR);
	if (tok == TOK_LABEL)
		*data = first_word(line, LABEL_CHAR);
	if (tok == TOK_STR)
		*data = first_word(&line[1], '"');
	return (1);
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
		while (line[c] && !is_space(line[c]) && line[c] != SEP_CHAR)
			c++;
		while (line[c] && is_space(line[c]))
			c++;
	}
	if (line[c] == SEP_CHAR)
		c++;
	while (is_space(line[c]))
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
	while (is_space(line[count]))
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

t_tok		*check_file(char *file)
{
	int		fd;
	int		nb_line;
	char	*line;
	t_tok	*first_tok;
	t_tok	*token;

	first_tok = NULL;
	first_tok = push_token(first_tok);
	first_tok->data = (void *)file;
	token = first_tok;
	if ((fd = open(file, O_RDONLY)) <= 1)
		return (NULL);
	nb_line = 1;
	while (get_next_line(fd, &line) > 0)
	{
		if (!(token = check_line(token, line)))
			return (NULL);
		free(line);
		nb_line++;
	}
	if (!verify_list(first_tok))
		return (NULL);
	compile(first_tok);
	return (first_tok);
}

int			main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	if (!check_file(argv[1]))
		ft_print("Error\n");
	else
		ft_print("Ok\n");
	return (0);
}
