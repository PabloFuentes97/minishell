/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:49:26 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/07 10:11:42 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 
#include "../libft/libft.h"

char	*char_to_str(int c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

int	skip_to_char(char *str, char c)
{
	int	pos;

	pos = 0;
	while (str[pos])
	{
		if (str[pos] == c)
			break ;
		pos++;
	}
	return (pos);
}

int	skip_spaces(char *str, int pos)
{
	while (str[pos] == ' ')
		pos++;
	return (pos);
}

int	last_word(char *str, int last)
{
	if (str[last] == ' ')
	{
		while (last >= 0 && str[last] == ' ')
			last--;
	}
	return (last);
}

int	next_word(char *str, int pos)
{
	while (str[pos] != ' ')
		pos++;
	return (pos);
}
