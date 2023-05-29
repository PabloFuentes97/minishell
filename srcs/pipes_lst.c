/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 09:33:32 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/28 13:18:20 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*static void	pipe_left(t_btree *root, t_executer *executer)
{
	t_token	*down;
	t_token	*down_par;
	t_pipe	*pipe;

	printf("Rama izquierda de pipe\n");
	down = get_token(root->left->content);
	if (down->type == OPEN_PAR)
		if (root->left->left)
			down_par = get_token(root->left->left->content);
	if (down->type != PIPE
		&& (down->type != OPEN_PAR || down_par->type != PIPE))
	{
		printf("Izquierda no es pipe, lo añado\n");
		if (!executer->pipes.pipes_lst)
			pipe = new_pipe_dir(executer->dirs.stdin, PIPE_WRITE);
		else
			pipe = new_pipe_dir(PIPE_READ, PIPE_WRITE);
		ft_lstadd_back(&executer->pipes.pipes_lst, ft_lstnew(pipe));
	}
}

static void	pipe_right(t_btree *root, t_executer *executer)
{
	t_token	*down;
	t_token	*down_par;
	t_pipe	*pipe;

	printf("Rama derecha de pipe\n");
	down = get_token(root->right->content);
	if (down->type == OPEN_PAR)
		if (root->right->left)
				down_par = get_token(root->right->left->content);
	if (down->type != PIPE
		&& (down->type != OPEN_PAR || down_par->type != PIPE))
	{
		printf("Derecha no es pipe, lo añado\n");
		if (down->type >= OR && down->type <= PIPE)
		{
			executer->pipes.pipes_group_num++;
		}
		if (executer->pipes.concat_left > 0)
			pipe = new_pipe_dir(PIPE_READ, PIPE_WRITE);
		else
			pipe = new_pipe_dir(PIPE_READ, executer->dirs.stdout);
		ft_lstadd_back(&executer->pipes.pipes_lst, ft_lstnew(pipe));
	}
}

void	set_pipe_lst(t_bree *root, t_executer *executer)
{
	t_token	*down_left;
	t_token	*down_right;

	down_left = get_token(root->left->content);
	if (down_left->type == OPEN_PAR)
		executer->pipes.concat_left++;
	pipe_left(root, executer);
	print_pipes_lst(executer->pipes.pipes_lst);
	execute_parser_tree(root->left, executer);
	printf("Vuelvo a subir a pipe\n");
	if (down_left->type == OPEN_PAR)
		executer->pipes.concat_left--;
	down_right = get_token(root->right->content);
	if (down_right->type == OPEN_PAR)
		executer->pipes.concat_right++;
	pipe_right(root, executer);
	print_pipes_lst(executer->pipes.pipes_lst);
	execute_parser_tree(root->right, executer);
	printf("Vuelvo a subir a pipe\n");
	if (down_right->type == OPEN_PAR)
		executer->pipes.concat_right--;
}

void	print_pipes_lst(t_list *pipes)
{
	t_pipe	*pipe;

	while (pipes)
	{
		pipe = (t_pipe *)pipes->content;
		printf("Input: %d, output: %d\n", pipe->input, pipe->output);
		pipes = pipes->next;
	}
}*/
