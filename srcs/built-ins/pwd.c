/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:44:04 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/05 13:44:33 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h" 
#include "../../libft/libft.h"

void	pwd(t_mshell *mshell)
{
	char	*pwd_str;

	pwd_str = NULL;
	pwd_str = getcwd(pwd_str, 10000000);
	if (pwd_str)
	{
		ft_putstr_fd(pwd_str, mshell->data.output);
		write(mshell->data.output, "\n", 1);
		mshell->data.last_cmd = 0;
	}
	free(pwd_str);
}
