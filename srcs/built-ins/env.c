/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:29:14 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/20 10:55:27 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

void	env(char **cmd, t_mshell *mshell)
{
	t_list	*env_lst;
	t_kv	*key_val;

	if (matrix_len(cmd) > 1)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		mshell->data.last_cmd = 1;
		mshell->data.last_err = 1;
		return ;
	}
	env_lst = mshell->data.env_lst;
	while (env_lst)
	{
		key_val = get_key_value(env_lst);
		ft_putstr_fd(key_val->key, mshell->data.output);
		ft_putstr_fd("=", mshell->data.output);
		ft_putstr_fd(key_val->value, mshell->data.output);
		ft_putstr_fd("\n", mshell->data.output);
		env_lst = env_lst->next;
	}
}
