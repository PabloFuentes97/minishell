#include "../includes/minishell.h"

void	trim_list(t_list **lst, int start, int end, void (*del)(void *))
{
	t_list	*last;
	int		pos;
	t_list	*aux;

	last = ft_lstlast(*lst);
	pos = 0;
	while (pos < end && last)
	{
		aux = last;
		last = last->prev;
		del(aux->content);
		free(aux);
		pos++;
	}
	pos = 0;
	while (pos < start && *lst)
	{
		aux = (*lst);
		(*lst) = (*lst)->next;
		del(aux->content);
		free(aux);
		pos++;
	}
}

void	tokens_delete_par(t_list **lst)
{
	t_list	*start;
	t_list	*end;

	start = (*lst);
	end = start;
	(*lst) = (*lst)->next;
	tokens_skip_par(&end);
	lst_delete_node(&start, &free_token); //borrar primer paréntesis
	end->prev->next = NULL;
	lst_delete_node(&end, &free_token); //borrar último paréntesis
}

int	is_parenthesis(t_btree **tree, t_list *tokens)
{
	t_token *token;

	if (tokens_check_operators(tokens) == 0
		&& get_token(tokens)->type == OPEN_PAR)
	{
		token = new_token(ft_strdup("()"));
		token->type = OPEN_PAR;
		(*tree)->content = ft_lstnew(token);
		tokens_delete_par(&tokens); //usar trim_list en vez de esta
		//trim_list(&tokens, 1, 1, &free_token);
		(*tree)->left = btree_new_node(tokens);
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
	curr->prev->next = NULL;
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

	tokens = (t_list *)(*tree)->content;
	if (is_parenthesis(tree, tokens) == 1)
		new_parser_tree(&(*tree)->left);
	else
	{
		curr = tokens;
		traverse_lst_until_op(&curr);
		if (curr)
			parser_tree_add_leaves(tree, tokens, curr);
	}
}
