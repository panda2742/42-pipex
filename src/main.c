/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:59:51 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/03 01:55:40 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	printerr(t_error_type error_type)
{
	ft_printf(RED "An error occured.\n" RESET);
	if (error_type == PIPEX_SYNTAX_ERROR)
	{
		ft_printf(GRAY " - Correct usage:\n" RESET);
		ft_printf(MAGENTA "   <input> <cmd1> <cmd2> <output>\n" RESET);
		ft_printf(GRAY "   ...where input is an existing file.\n" RESET);
	}
	else if (error_type == MALLOC_ERROR)
		ft_printf(GRAY "Memory allocation failed." RESET);
}

int	main(int argc, char **argv)
{
	t_pipex	*pipex;

	if (argc < 5)
		return (printerr(PIPEX_SYNTAX_ERROR), EXIT_FAILURE);
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (printerr(MALLOC_ERROR), EXIT_FAILURE);
	pipex->infile = init_file((const char *)argv[1], O_RDONLY);
	if (!pipex->infile->is_valid)
		return (printerr(PIPEX_SYNTAX_ERROR), EXIT_FAILURE);
	pipex->outfile = init_file((const char *)argv[argc - 1], O_RDWR);
	read_infile(pipex->infile);
	clear_pipex(pipex);
	return (0);
}

void	clear_pipex(t_pipex *pipex)
{
	if (pipex->infile->content)
		free((void *)pipex->infile->content);
	free(pipex->infile);
	if (pipex->outfile->content)
		free((void *)pipex->outfile->content);
	free(pipex->outfile);
	free(pipex);
}
