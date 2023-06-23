/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:47:29 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/22 11:48:46 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

void	cmd_op(t_list **tokens, t_mshell *mshell)
{
	char	**cmd;
	t_list	*curr;

	check_sustitution(*tokens, mshell);
	curr = *tokens;
	if (check_var_assignment(&curr, mshell) == 0)
	{
		if (set_redirections(*tokens, mshell) == 1)
			search_cmd(mshell, curr);
	}
	after_execute_cmd(mshell);
}
