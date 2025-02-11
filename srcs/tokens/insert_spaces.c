/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:35:59 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/03 10:39:45 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_operator_size(char *op)
{
	if (op[0] == op[1])
		return (2);
	return (1);
}

static char	*create_new_line(char *op, char *line_init, int op_size)
{
	char	*new;
	char	*left;
	char	*right;
	char	*op_dup;

	left = ft_substr(line_init, 0, ft_strlen(line_init) - ft_strlen(op));
	if (left == NULL)
		return (NULL);
	right = ft_substr(op, op_size, ft_strlen(op));
	if (right == NULL)
		return (free(left), NULL);
	op_dup = ft_strndup(op, op_size);
	if (op_dup == NULL)
		return (free(left), free(right), NULL);
	new = variadic_strjoin(5, left, " ", op_dup, " ", right);
	free(left);
	free(right);
	free(op_dup);
	return (new);
}

char	*insert_spaces(char *op, char *line_init, int *i)
{
	int		op_size;
	char	*new_line;

	op_size = get_operator_size(op);
	new_line = create_new_line(op, line_init, op_size);
	if (new_line)
		*i += op_size + 1;
	return (new_line);
}
