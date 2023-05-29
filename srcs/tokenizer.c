/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 09:13:30 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/29 09:24:32 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 

static int	char_pos(char *str, char c)
{
	int	pos;

	pos = 0;
	while (str[pos])
	{
		if (str[pos] == c)
			break ;
		pos++;
	}
	return (pos);
}

void	in_dict(t_lexer *lexer)
{
	int	i;
	int	op_len;

	i = 0;
	while (i < DOLLAR - 1)
	{
		op_len = ft_strlen(lexer->dict[i]);
		if (ft_strncmp(lexer->dict[i],
				&lexer->line[lexer->tokenizer->end], op_len) == 0)
		{
			lexer->tokenizer->op_len = op_len;
			return ;
		}
		i++;
	}
	lexer->tokenizer->op_len = 0;
}

void	add_token_lst(t_lexer *lexer, int type)
{
	char	*str;
	t_token	*token;
	t_list	*new;

	if (type == 0)
		str = ft_substr(lexer->line, lexer->tokenizer->start,
				lexer->tokenizer->end - lexer->tokenizer->start);
	else
		str = ft_substr(lexer->line, lexer->tokenizer->end,
				lexer->tokenizer->op_len);
	token = new_token(str);
	new = ft_lstnew(token);
	ft_lstadd_back(&lexer->tokens, new);
}

void	add_tokens_quotes(t_lexer *lexer, int type)
{
	lexer->tokenizer->end++;
	lexer->tokenizer->start = lexer->tokenizer->end;
	if (type == 0)
		lexer->tokenizer->end
			+= char_pos(&lexer->line[lexer->tokenizer->end], 34);
	else if (type == 1)
		lexer->tokenizer->end
			+= char_pos(&lexer->line[lexer->tokenizer->end], 39);
	add_token_lst(lexer, 0);
	if (lexer->line[lexer->tokenizer->end] != '\0')
		add_token_lst(lexer, 1);
	lexer->tokenizer->end++;
	lexer->tokenizer->start = lexer->tokenizer->end;
}

void	add_tokens_assign(t_lexer *lexer)
{
	lexer->tokenizer->end++;
	lexer->tokenizer->start = lexer->tokenizer->end;
	lexer->tokenizer->end
		+= char_pos(&lexer->line[lexer->tokenizer->end], 32);
	add_token_lst(lexer, 0);
	lexer->tokenizer->start = lexer->tokenizer->end;
}

void	special_symbols(t_lexer *lexer)
{
	if (lexer->line[lexer->tokenizer->end] == 34)
		add_tokens_quotes(lexer, 0);
	else if (lexer->line[lexer->tokenizer->end] == 39)
		add_tokens_quotes(lexer, 1);
	else if (lexer->line[lexer->tokenizer->end] == 61)
		add_tokens_assign(lexer);
	else
	{
		lexer->tokenizer->end += lexer->tokenizer->op_len;
		lexer->tokenizer->start = lexer->tokenizer->end;
	}
}

void	tokens_lst(t_lexer *lexer)
{
	while (lexer->line[lexer->tokenizer->end])
	{
		lexer->tokenizer->end = skip_spaces(lexer->line, lexer->tokenizer->end);
		lexer->tokenizer->start = lexer->tokenizer->end;
		while (lexer->line[lexer->tokenizer->end]
			&& lexer->line[lexer->tokenizer->end] != ' ')
		{
			in_dict(lexer);
			if (lexer->tokenizer->op_len > 0)
			{
				if (lexer->tokenizer->start != lexer->tokenizer->end)
					add_token_lst(lexer, 0);
				add_token_lst(lexer, 1);
				special_symbols(lexer);
			}
			else
				lexer->tokenizer->end++;
		}
		if (lexer->tokenizer->start != lexer->tokenizer->end)
			add_token_lst(lexer, 0);
	}
}

void	print_tokens_lst(t_list *tokens)
{
	t_token	*token;

	while (tokens)
	{
		token = (t_token *)tokens->content;
		printf("%s$:  %d\n", token->str, token->type);
		tokens = tokens->next;
	}
}
