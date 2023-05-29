/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:58:27 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/29 09:27:52 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

void	subshell(t_btree *root, t_executer *executer)
{
	int		pid;
	int		wstatus;
	//printf("Entro en subshell\n");
	pid = fork();
	if (pid == 0)
	{
		executer->shell_lev++;
		execute_parser_tree(root->left, executer);
		free_parser_tree(&executer->root);
		b_exit(errno);
	}
	else
	{
		waitpid(pid, &wstatus, 0);
		cmd_return(executer, wstatus);
	}
}

int	*int_ptr(int num)
{
	int	*ptr;

	ptr = malloc(sizeof(int));
	*ptr = num;
	return (ptr);
}

void	waitpid_pids(t_executer *executer)
{
	t_list	*pids;
	int		wstatus;
	int		*pid;

	printf("En waitpid_pipes\n");
	pids = executer->ops->pids_lst;
	while (pids)
	{
		pid = (int *)pids->content;
		printf("PID de proceso a esperar: %d\n", *pid);
		waitpid(*pid, &wstatus, 0);
		cmd_return(executer, wstatus);
		pids = pids->next;
	}
	ft_lstclear(&executer->ops->pids_lst, &free);
}


void	pipe_op(t_btree *root, t_executer *executer)
{
	execute_parser_tree(root->left, executer);
	execute_parser_tree(root->right, executer);
}

void	and_op(t_btree *root, t_executer *executer)
{
	execute_parser_tree(root->left, executer);
	if (executer->last_return == 0)
		execute_parser_tree(root->right, executer);
}

void	or_op(t_btree *root, t_executer *executer)
{
	execute_parser_tree(root->left, executer);
	if (executer->last_return != 0)
		execute_parser_tree(root->right, executer);
}

void	here_doc_dir(t_dirs *dirs)
{
	int		fd;

	dirs->input_file = ft_strdup((char *)dirs->here_docs->content);
	fd = open(dirs->input_file, O_RDONLY, 0666);
	dirs->input = fd;
	printf("Fd de here_doc: %d\n", fd);
	dirs->here_doc_num = 1;
	remove_head(&dirs->here_docs);
	printf("Estoy en here_doc, nombre de archivo es: %s\n", dirs->input_file);
}
