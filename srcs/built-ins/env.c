/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:29:14 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/05 12:35:26 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

void	env(t_mshell *mshell)
{
	t_list	*env_lst;
	t_kv	*key_val;

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
