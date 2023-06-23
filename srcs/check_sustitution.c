/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sustitution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 09:28:19 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/22 11:38:37 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 
#include "../libft/libft.h"

void	inside_dquote(t_token *token, int *inside)
{
	if (token->type == D_QUOTE)
	{
		if (*inside == 0)
			*inside = 1;
		else
			*inside = 0;
	}
}

void	check_sustitution(t_list *tokens, t_mshell *mshell)
{
	t_token	*token;
	int		dquote;

	dquote = 0;
	while (tokens)
	{
		token = get_token(tokens);
		if (token->type == D_QUOTE)
			inside_dquote(token, &dquote);
		else if (token->type == QUOTE && dquote == 0)
		{
			tokens = tokens->next;
			tokens_skip(&tokens, QUOTE);
		}
		else if (token->type == DOLLAR || token->type == WILD_CARDS)
		{
			if (token->type == DOLLAR)
				token->str = dollar_expansion(token->str, mshell);
			else if (token->type == WILD_CARDS)
				token->str = call_wildcards(token->str);
			token->type = 0;
		}
		tokens = tokens->next;
	}
}
