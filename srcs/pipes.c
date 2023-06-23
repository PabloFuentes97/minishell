/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:19:48 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/22 15:52:51 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

void	new_pipes(t_mshell *mshell)
{
	t_dir	*dir;

	pipe(mshell->data.pipes);
	dir = get_dir(mshell->data.op_lst);
	if (dir->input == PIPE_READ)
		mshell->data.input = mshell->data.pipes[0];
	else
		mshell->data.input = mshell->data.stdin;
	if (dir->output == PIPE_WRITE)
		mshell->data.output = mshell->data.pipes[1];
	else
		mshell->data.output = mshell->data.stdout;
}

void	close_pipes(t_mshell *mshell, int type)
{
	close(mshell->data.pipes[1]);
	if (type == 1)
		close(mshell->data.pipes[0]);
	if (type == 0 && get_dir(mshell->data.op_lst)->output != PIPE_WRITE)
		close(mshell->data.pipes[0]);
}
