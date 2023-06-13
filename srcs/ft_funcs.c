/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_funcs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:56:05 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/07 11:55:12 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

int	ft_dup(int fd)
{
	int	dup_fd;

	dup_fd = dup(fd);
	if (dup_fd < 0)
		b_exit(errno);
	return (dup_fd);
}

void	ft_dup2(int fd1, int fd2)
{
	int	value;

	value = dup2(fd1, fd2);
	if (value < 0)
		b_exit(errno);
}

void	ft_close(int fd)
{
	int	value;

	value = close(fd);
	if (value < 0)
		b_exit(errno);
}

void	*ft_malloc(int size)
{
	void	*allocate;

	allocate = malloc(size);
	if (!allocate)
		b_exit(19);
	return (allocate);
}
