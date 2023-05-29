/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 09:26:25 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/29 09:34:00 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h" 

void	unset(char **cmd, t_executer *executer)
{
	int		cont;
	t_list	*to_delete;

	cont = 1;
	while (cmd[cont])
	{
		to_delete = get_node_by_key(executer->env->env_lst, cmd[cont]);
		if (!to_delete)
		{
			executer->last_return = 1;
			return ;
		}
		lst_delete_node(&to_delete, &free_key_value);
		cont++;
	}
	executer->last_return = 0;
}
