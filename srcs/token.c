/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:52:22 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/13 16:37:33 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 
#include "../libft/libft.h"

t_token	*new_token(char *str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->str = str;
	token->type = 0;
	return (token);
}

t_token	*get_token(t_list *node)
{
	t_token	*token;

	token = (t_token *)node->content;
	return (token);
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

void	assign_tokens_type(t_list **tokens, char **dict)
{
	t_list	*curr;
	t_token	*token;

	curr = *tokens;
	while (curr)
	{
		token = get_token(curr);
		token->type = token_type(token->str, dict);
		curr = curr->next;
	}
}
