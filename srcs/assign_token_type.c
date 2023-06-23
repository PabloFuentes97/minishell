/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_token_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:52:22 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/16 11:38:26 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 
#include "../libft/libft.h"

int	token_type(char *cmp, char **dict)
{
	int		cont;

	cont = 0;
	while (dict[cont])
	{
		if (cont < DOLLAR - 1)
		{
			if (ft_strncmp(cmp, dict[cont], ft_strlen(dict[cont])) == 0)
				return (cont + 1);
		}
		else
			if (ft_strnstr(cmp, dict[cont], ft_strlen(cmp)))
				return (cont + 1);
		cont++;
	}
	return (0);
}

static void	tokens_inside_quotes(t_list **tokens, char **dict)
{
	char	*quote;
	t_token	*token;

	token = get_token(*tokens);
	quote = token->str;
	*tokens = (*tokens)->next;
	while (*tokens)
	{
		token = get_token(*tokens);
		if (ft_strchr(token->str, '$'))
			token->type = DOLLAR;
		else if (ft_strchr(token->str, '*'))
			token->type = WILD_CARDS;
		else if (ft_strncmp(quote, token->str, ft_strlen(quote)) == 0)
		{
			token->type = token_type(token->str, dict);
			*tokens = (*tokens)->next;
			return ;
		}
		*tokens = (*tokens)->next;
	}
}

void	assign_tokens_type(t_list **tokens, char **dict)
{
	t_list	*curr;
	t_token	*token;
	char	*quote;

	curr = *tokens;
	while (curr)
	{
		token = get_token(curr);
		token->type = token_type(token->str, dict);
		if (token->type == QUOTE || token->type == D_QUOTE)
			tokens_inside_quotes(&curr, dict);
		else
			curr = curr->next;
	}
}
