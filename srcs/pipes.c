/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:19:48 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/29 11:27:13 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	new_pipe(t_executer *executer)
{
	t_dir	*dir;
	int		*fd;

	printf("Dentro de pipes_dir\n");
	dir = get_dir(executer->ops->op_lst);
	fd = malloc(sizeof(int) * 2);
	pipe(fd);
	printf("Input: %d y output: %d antes\n",
		executer->dirs->input, executer->dirs->output);
	ft_lstadd_back(&executer->ops->pipes_lst, ft_lstnew(fd));
	if (dir->input == PIPE_READ)
		executer->dirs->input = fd[0];
	else
	{
		executer->dirs->input = executer->dirs->stdin;
		//close(fd[0]);
	}
	if (dir->output == PIPE_WRITE)
		executer->dirs->output = fd[1];
	else
	{
		executer->dirs->output = executer->dirs->stdout;
		//close(fd[1]);
	}
	printf("Input: %d y output: %d después\n",
		executer->dirs->input, executer->dirs->output);
}

void	close_pipe(t_executer *executer)
{
	int	*fd;

	perror("En close pipe\n");
	printf("\n\n\n\n");
	fd = (int *)executer->ops->pipes_lst->content;
	close(fd[0]);
	close(fd[1]);
	perror("Después de cerrar pipe\n\n\n\n");
	remove_head(&executer->ops->pipes_lst);
}
