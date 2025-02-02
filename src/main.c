/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:59:51 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/02 22:58:52 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv)
{
	t_pipex	*pipex;

	if (argc < 5)
		return (ft_printf("Error.\n"), EXIT_FAILURE);
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (ft_printf("Malloc error.\n"), EXIT_FAILURE);
	pipex->infile = init_file((const char *)argv[1], O_RDONLY);
	if (!pipex->infile->is_valid)
		return (ft_printf("Wrong input file.\n"), EXIT_FAILURE);
	pipex->outfile = init_file((const char *)argv[argc - 1], O_RDWR);
	read_infile(pipex->infile);
	ft_printf("infile: \n%s", pipex->infile->content);
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
