#include "../includes/minishell.h"
#include "../libft/libft.h"


void	tokens_skip(t_list **lst, int type)
{
	t_token	*token;

	token = (t_token *)(*lst)->content;
	*lst = (*lst)->next;
	token = (t_token *)(*lst)->content;
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

int	lst_node_pos(t_list *lst, t_list *node)
{
	int	pos;

	pos = 0;
	while (lst)
	{
		if (lst == node)
			return (pos);
		pos++;
		lst = lst->next;
	}
	return (-1);
}

void	lst_move_pos(t_list **lst, int pos)
{
	int	i;

	i = 0;
	while (i < pos)
	{
		i++;
		(*lst) = (*lst)->next;
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

void	lst_divide_by_pos(t_list	**start, int end)
{
	int		i;
	t_list	*curr;

	i = 0;
	curr = *start;
	while (i < end - 1)
	{
		curr = curr->next;
		i++;
	}
	curr->next = NULL;
}
