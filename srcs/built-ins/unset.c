/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:43:54 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/21 13:25:07 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h" 
#include "../../libft/libft.h"

void	unset(char **cmd, t_list **env_lst, t_mshell *mshell)
{
	int		cont;
	t_list	*to_delete;

	if (matrix_len(cmd) == 1)
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		mshell->data.last_cmd = 1;
		mshell->data.last_err = 1;
		return ;
	}
	cont = 1;
	while (cmd[cont])
	{
		to_delete = get_node_by_key(*env_lst, cmd[cont]);
		if (to_delete && to_delete == *env_lst)
			*env_lst = (*env_lst)->next;
		if (to_delete)
			lst_delete_node(&to_delete, &free_key_value);
		cont++;
	}
	mshell->data.last_cmd = 0;
}
