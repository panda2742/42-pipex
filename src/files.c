/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:27:25 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/02 17:32:25 by ehosta           ###   ########.fr       */
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
	if (file->fd == -1)
		file->is_valid = FALSE;
	return (file);
}