/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 09:14:32 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/29 09:25:23 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 

t_token	*new_token(char *str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->str = str;
	token->type = 0;
	return (token);
}

void	set_tokens_type(t_lexer *lexer)
{
	t_list	*curr;
	t_token	*token;

	curr = lexer->tokens;
	while (curr)
	{
		token = get_token(curr);
		token->type = set_token_type(token->str, lexer->dict);
		curr = curr->next;
	}
}

int	set_token_type(char *cmp, char **dict)
{
	int		cont;

	cont = 0;
	while (dict[cont])
	{
		if (cont < DOLLAR - 1)
		{
			if (ft_strncmp(cmp, dict[cont], longer_str(cmp, dict[cont])) == 0)
				return (cont + 1);
		}
		else
		{
			if (ft_strnstr(cmp, dict[cont], ft_strlen(cmp)))
				return (cont + 1);
		}
		cont++;
	}
	return (0);
}

void	free_token(void *content)
{
	t_token	*token;

	if (content)
	{
		token = (t_token *)content;
		if (token)
		{
			free(token->str);
			free(token);
			token = NULL;
		}
	}
}
