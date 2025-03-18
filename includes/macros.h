/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:22:45 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/18 13:48:53 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define MALLOC_ERROR 1
# define ERROR_CWD 2

# define CMD 1
# define PIPE 2
# define REDIRECT 3

# define OR 5
# define AND 6

# define PIPE_ERROR "minishell: syntax error near unexpected token `|'\n"
# define T_ERROR "minishell: syntax error near unexpected token `%s'\n"
# define NL_ERROR "minishell: syntax error near unexpected token `newline'\n"
# define HDOC_ERROR "minishell: warning: here-document delimited by \
	end-of-file (wanted `%s')\n"
# define FILE_ERROR "minishell: %s: No such file or directory\n"
# define PERM_ERROR "minishell: %s: Permission denied\n"

#endif
