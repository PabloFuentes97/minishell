/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:58:15 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/07 10:08:44 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

void	op_lst(t_btree *root, t_mshell *mshell)
{
	t_token	*token;

	if (!root)
		return ;
	token = get_token(root->content);
	if (token->type >= OR
		&& token->type <= PIPE)
	{
		if (token->type == PIPE)
			op_add_pipes(root, mshell);
		else if (token->type == OR)
			op_add_or_and(root, mshell, OR);
		else if (token->type == AND)
			op_add_or_and(root, mshell, AND);
	}
}

void	assign_dirs_op(t_mshell *mshell)
{
	t_list	*curr;
	t_dir	*dir;

	curr = mshell->data.op_lst;
	while (curr)
	{
		dir = get_dir(curr);
		if (dir->type == PIPE)
		{
			if (!curr->prev || get_dir(curr->prev)->type != PIPE)
				dir->input = mshell->data.stdin;
			else
				dir->input = PIPE_READ;
			if (!curr->next || get_dir(curr->next)->type != PIPE)
				dir->output = mshell->data.stdout;
			else
				dir->output = PIPE_WRITE;
		}
		else
		{
			dir->input = mshell->data.stdin;
			dir->output = mshell->data.stdout;
		}
		curr = curr->next;
	}
}

void	print_op_lst(t_list *lst)
{
	t_dir	*dir;

	while (lst)
	{
		printf("Op: \n");
		dir = get_dir(lst);
		printf("Tipo: %d\n", dir->type);
		printf("Input: %d\n", dir->input);
		printf("Output: %d\n", dir->output);
		lst = lst->next;
	}
}
