/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:52:22 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/16 10:47:59 by pfuentes         ###   ########.fr       */
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
