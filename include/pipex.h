/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:59:49 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/03 01:49:44 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/include/libft.h"

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum e_error_type
{
	PIPEX_SYNTAX_ERROR,
	MALLOC_ERROR
}	t_error_type;

typedef struct s_pipex_file
{
	const char	*filename;
	int			fd;
	t_bool		is_valid;
	const char	*content;
}	t_pipex_file;

typedef struct s_pipe_cmd
{
	const char	*cmd;
	const char	*input;
	char		*output;
}	t_pipe_cmd;

typedef struct s_pipex
{
	t_pipex_file	*infile;
	t_pipex_file	*outfile;	
	t_pipe_cmd		**cmds;
}	t_pipex;

t_pipex_file	*init_file(const char *filename, int open_mode);
t_pipex_file	*read_infile(t_pipex_file *infile);
void			clear_pipex(t_pipex *pipex);

#endif