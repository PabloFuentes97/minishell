/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:12:49 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/07 12:26:19 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

int	syntax_analizer(t_list *tokens)
{
	if (valid_num_par(tokens) == 0)
		return (0);
	if (valid_num_quotes(tokens) == 0)
		return (0);
	if (valid_redirections(tokens) == 0)
		return (0);
	if (valid_op_pos(tokens) == 0)
		return (0);
	if (valid_par_pos(tokens) == 0)
		return (0);
	if (valid_assignment(tokens) == 0)
		return (0);
	return (1);
}
