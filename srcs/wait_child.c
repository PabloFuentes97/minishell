/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 09:57:25 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/10 12:22:18 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

void	waitpid_pids(t_mshell *mshell)
{
	t_list	*pids;
	int		wstatus;
	int		*pid;

	pids = mshell->data.pids_lst;
	while (pids)
	{
		pid = (int *)pids->content;
		signals_parent_wait();
		waitpid(*pid, &wstatus, 0);
		signals_parent();
		cmd_return(mshell, wstatus);
		pids = pids->next;
	}
	ft_lstclear(&mshell->data.pids_lst, &free);
}

void	cmd_return(t_mshell *mshell, int status)
{
	int	statuscode;

	printf("Entro en cmd return\n");
	if (WIFEXITED(status) || WIFSIGNALED(status))
	{
		statuscode = WEXITSTATUS(status);
		printf("Código de salida: %d\n", statuscode);
		if (statuscode != 0)
		{
			errno = statuscode;
			mshell->data.last_err = errno;
			printf("Ejecutó con algún error\n");
		}
		if (WIFSIGNALED(status))
			mshell->data.last_cmd = errno;
		else
			mshell->data.last_cmd = statuscode;
		mshell->data.last_err = errno;
		printf("Errno: %d\n", errno);
	}
}

int	*int_ptr(int num)
{
	int	*ptr;

	ptr = malloc(sizeof(int));
	*ptr = num;
	return (ptr);
}

void	parent_wait_cmd(t_mshell *mshell, int pid, int wstatus)
{
	if (mshell->data.op_lst)
	{
		if (get_dir(mshell->data.op_lst)->type == PIPE)
			ft_lstadd_back(&mshell->data.pids_lst, ft_lstnew(int_ptr(pid)));
	}
	else
	{
		signals_parent_wait();
		waitpid(pid, &wstatus, 0);
		signals_parent();
		cmd_return(mshell, wstatus);
	}
}
