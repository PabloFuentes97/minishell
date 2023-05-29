/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:58:15 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/28 13:40:33 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_dir	*new_dir(int input, int output, int type)
{
	t_dir	*dir;

	dir = malloc(sizeof(t_dir));
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

void	free_dir(t_dir *dir)
{
	free(dir->pipe);
	dir = NULL;
}