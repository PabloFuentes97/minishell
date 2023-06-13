/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:30:35 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/07 11:54:23 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

t_dir	*new_dir(int input, int output, int type)
{
	t_dir	*dir;

	dir = malloc(sizeof(dir));
	dir->input = input;
	dir->output = output;
	dir->type = type;
	return (dir);
}

t_dir	*get_dir(t_list *node)
{
	t_dir	*dir;

	dir = (t_dir *)node->content;
	return (dir);
}
