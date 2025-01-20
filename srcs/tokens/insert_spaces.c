/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:35:59 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/20 21:54:04 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_operator_size(char *op)
{
	if (*op == *(op + 1))
		return (2);
	return (1);
}

static char	*create_new_line(char *line, char *op, int op_size,
							int offset)
{
	char	*new;
	char	*left;
	char	*op_dup;
	char	*right;

	left = ft_substr(line, 0, offset);
	op_dup = ft_substr(op, 0, op_size);
	right = ft_strdup(op + op_size);
	new = variadic_strjoin(5, left, " ", op, " ", right);
	free(left);
	free(op_dup);
	free(right);
	return (new);
}

char	*insert_spaces(char *line, char *op, char *line_init)
{
	char	*new;
	int		op_size;
	int		offset;

	if (op != line_init)
	{
		if (*(op - 1) == '>' || *(op - 1) == '<')
			return (op++);
	}
	op_size = get_operator_size(op);
	offset = op - line;
	new = create_new_line(line, op, op_size, offset);
	free(line);
	return (new + offset + op_size + 1);
}
