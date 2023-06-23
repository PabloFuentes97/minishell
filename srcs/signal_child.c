/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:28:44 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/20 10:21:05 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 
#include "../libft/libft.h"

void	ctrl_4_signal_child(void)
{
	ft_putstr_fd("Quit: 3\n", 2);
	exit(131);
}

void	signal_handler_child(int signal)
{
	if (signal == SIGINT)
		exit(130);
	else if (signal == SIGQUIT)
		ctrl_4_signal_child();
}

void	signal_handler_parent_wait(int signal)
{
	if (signal == SIGINT)
		errno = 130;
	else if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		errno = 131;
	}
}

void	signals_parent_wait(void)
{
	signal(SIGINT, &signal_handler_parent_wait);
	signal(SIGQUIT, &signal_handler_parent_wait);
}

void	signals_child(void)
{
	signal(SIGINT, &signal_handler_child);
	signal(SIGQUIT, &signal_handler_child);
}
