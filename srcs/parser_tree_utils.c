/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tree_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 09:16:01 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/15 14:10:15 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

void	tokens_skip(t_list **lst, int type)
{
	t_token	*token;

	*lst = (*lst)->next;
	while (*lst)
	{
		token = (t_token *)(*lst)->content;
		if (token->type == type)
			return ;
		*lst = (*lst)->next;
	}
}

void	tokens_skip_par(t_list **lst)
{
	int		open;
	int		close;
	t_token	*token;

	open = 0;
	close = 0;
	while (*lst)
	{
		token = (t_token *)(*lst)->content;
		if (token->type == OPEN_PAR)
			open++;
		else if (token->type == CLOSE_PAR)
			close++;
		if (open == close)
			return ;
		*lst = (*lst)->next;
	}
}

int	tokens_check_operators(t_list	*lst)
{
	t_token	*token;

	while (lst)
	{
		token = (t_token *)lst->content;
		if (token->type > CMD && token->type < HERE_DOC)
			return (1);
		if (token->type == QUOTE)
			tokens_skip(&lst, QUOTE);
		else if (token->type == D_QUOTE)
			tokens_skip(&lst, D_QUOTE);
		else if (token->type == OPEN_PAR)
			tokens_skip_par(&lst);
		lst = lst->next;
	}
	return (0);
}
