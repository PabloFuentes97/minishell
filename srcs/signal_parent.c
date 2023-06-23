/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_parent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:16:12 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/10 12:21:56 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 
#include "../libft/libft.h"

void	ctrl_c_signal(void)
{
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler_parent(int signal)
{
	if (signal == SIGINT)
		ctrl_c_signal();
}

void	signals_parent(void)
{
	signal(SIGINT, &signal_handler_parent);
	signal(SIGQUIT, SIG_IGN);
}
