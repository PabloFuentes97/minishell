/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:49:47 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/07 12:17:10 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

void	tokens_delete_par(t_list **lst)
{
	t_list	*start;
	t_list	*end;

	start = (*lst);
	end = start;
	(*lst) = (*lst)->next;
	tokens_skip_par(&end);
	lst_delete_node(&start, &free_token);
	end->prev->next = NULL;
	lst_delete_node(&end, &free_token);
}

int	is_parenthesis(t_btree **tree, t_list **tokens)
{
	t_token	*token;
	t_list	*curr;

	curr = *tokens;
	if (tokens_check_operators(curr) == 0
		&& get_token(curr)->type == OPEN_PAR)
	{
		tokens_delete_par(tokens);
		(*tree)->content = *tokens;
		return (1);
	}
	else
		return (0);
}

void	traverse_lst_until_op(t_list **tokens)
{
	t_token	*token;

	while (*tokens)
	{
		token = (t_token *)(*tokens)->content;
		if (token->type == QUOTE)
			tokens_skip(tokens, QUOTE);
		else if (token->type == D_QUOTE)
			tokens_skip(tokens, D_QUOTE);
		else if (token->type == OPEN_PAR)
			tokens_skip_par(tokens);
		else if (token->type > 0 && token->type < 4)
			return ;
		*tokens = (*tokens)->next;
	}
}

void	parser_tree_add_leaves(t_btree **tree, t_list *tokens, t_list *curr)
{
	btree_add_right_node(tree, btree_new_node(curr->next));
	if (curr->prev)
		curr->prev->next = NULL;
	if (curr->next)
		curr->next->prev = NULL;
	btree_add_left_node(tree, btree_new_node(tokens));
	curr->prev = NULL;
	curr->next = NULL;
	(*tree)->content = curr;
	new_parser_tree(&(*tree)->left);
	new_parser_tree(&(*tree)->right);
}

void	new_parser_tree(t_btree **tree)
{
	t_list	*tokens;
	t_list	*curr;

	if (!*tree)
		return ;
	tokens = (t_list *)(*tree)->content;
	is_parenthesis(tree, &tokens);
	curr = tokens;
	traverse_lst_until_op(&curr);
	if (curr)
		parser_tree_add_leaves(tree, tokens, curr);
}
