/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:44:04 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/20 10:55:44 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h" 
#include "../../libft/libft.h"

void	pwd(char **cmd, t_mshell *mshell)
{
	char	*pwd_str;

	if (matrix_len(cmd) > 1)
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		mshell->data.last_cmd = 1;
		mshell->data.last_err = 1;
		return ;
	}
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
