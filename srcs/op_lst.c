/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:58:15 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/29 09:18:42 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	and_or_dir(t_executer *executer, int type)
{
	if (type == OR)
		ft_lstadd_back(&executer->ops->op_lst,
			ft_lstnew(new_dir(executer->dirs->stdin,
					executer->dirs->stdout, OR)));
	else if (type == AND)
		ft_lstadd_back(&executer->ops->op_lst,
			ft_lstnew(new_dir(executer->dirs->stdin,
					executer->dirs->stdout, AND)));
}

static void	pipe_left(t_btree *root, t_executer *executer)
{
	t_token	*down;
	t_token	*down_par;
	t_dir	*pipe;

	printf("Rama izquierda de pipe\n");
	down = get_token(root->left->content);
	if (down->type == OPEN_PAR)
		if (root->left->left)
			down_par = get_token(root->left->left->content);
	if (down->type != PIPE
		&& (down->type != OPEN_PAR || down_par->type != PIPE))
	{
		printf("Izquierda no es pipe, lo añado\n");
		if (!executer->ops->op_lst
			|| (root->up && get_token(root->up->content)->type != PIPE))
			pipe = new_dir(executer->dirs->stdin, PIPE_WRITE, PIPE);
		else
			pipe = new_dir(PIPE_READ, PIPE_WRITE, PIPE);
		ft_lstadd_back(&executer->ops->op_lst, ft_lstnew(pipe));
	}
}

static void	pipe_right(t_btree *root, t_executer *executer)
{
	t_token	*down;
	t_token	*down_par;
	t_dir	*pipe;

	printf("Rama derecha de pipe\n");
	down = get_token(root->right->content);
	if (down->type == OPEN_PAR)
		if (root->right->left)
				down_par = get_token(root->right->left->content);
	if (down->type != PIPE
		&& (down->type != OPEN_PAR || down_par->type != PIPE))
	{
		printf("Derecha no es pipe, lo añado\n");
		if (executer->ops->concat_left > 0)
			pipe = new_dir(PIPE_READ, PIPE_WRITE, PIPE);
		else
			pipe = new_dir(PIPE_READ, executer->dirs->stdout, PIPE);
		ft_lstadd_back(&executer->ops->op_lst, ft_lstnew(pipe));
	}
}

static void	op_add_pipes(t_btree *root, t_executer *executer)
{
	t_token	*down_left;
	t_token	*down_right;

	down_left = get_token(root->left->content);
	if (down_left->type == OPEN_PAR)
		executer->ops->concat_left++;
	pipe_left(root, executer);
	op_lst(root->left, executer);
	if (down_left->type == OPEN_PAR)
		executer->ops->concat_left--;
	down_right = get_token(root->right->content);
	if (down_right->type == OPEN_PAR)
		executer->ops->concat_right++;
	pipe_right(root, executer);
	op_lst(root->right, executer);
	if (down_right->type == OPEN_PAR)
		executer->ops->concat_right--;
}

static void	op_add_or_and(t_btree *root, t_executer *executer, int type)
{
	if (!root->up || (root->up && get_token(root->up->content)->type != PIPE))
	{
		if (get_token(root->left->content)->type <= CMD
			|| get_token(root->left->content)->type >= HERE_DOC)
			and_or_dir(executer, type);
		else
			op_lst(root->left, executer);
		if (get_token(root->right->content)->type <= CMD
			|| get_token(root->right->content)->type >= HERE_DOC)
			and_or_dir(executer, type);
		else
			op_lst(root->right, executer);
	}
	else
	{
		if (get_token(root->right->content)->type <= CMD
			|| get_token(root->right->content)->type >= HERE_DOC)
			and_or_dir(executer, type);
		else
			op_lst(root->right, executer);
	}
}

void	op_lst(t_btree *root, t_executer *executer)
{
	t_token	*token;

	if (!root)
		return ;
	token = get_token(root->content);
	if (token->type == OPEN_PAR)
		op_lst(root->left, executer);
	if (token->type >= OR
		&& token->type <= PIPE)
	{
		if (token->type == PIPE)
			op_add_pipes(root, executer);
		else if (token->type == OR)
			op_add_or_and(root, executer, OR);
		else if (token->type == AND)
			op_add_or_and(root, executer, AND);
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