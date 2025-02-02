/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:27:25 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/02 22:58:18 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_pipex_file	*init_file(const char *filename, int open_mode)
{
	t_pipex_file	*file;

	file = malloc(sizeof(t_pipex_file));
	if (!file)
		return (NULL);
	file->filename = filename;
	file->fd = open(filename, open_mode);
	file->is_valid = TRUE;
	file->content = NULL;
	if (file->fd == -1)
		file->is_valid = FALSE;
	return (file);
}

t_pipex_file	*read_infile(t_pipex_file *infile)
{
	char	*line;
	char	*content;
	char	*tmp;

	line = get_next_line(infile->fd);
	content = NULL;
	while (line)
	{
		tmp = content;
		content = ft_strjoin(tmp, line);
		if (tmp)
			free(tmp);
		free(line);
		line = get_next_line(infile->fd);
	}
	infile->content = content;
	return (infile);
}
