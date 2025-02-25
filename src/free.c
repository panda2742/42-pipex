/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:31:22 by mlazzare          #+#    #+#             */
/*   Updated: 2025/02/25 16:20:15 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_struct(t_cmd *c)
{
	int	i;

	i = 0;
	if (c->cmd)
		free(c->cmd);
	ft_free_strtab(c->path);
	while (c->args[i])
		free(c->args[i++]);
}

t_bool	check_empty(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != ' ')
			return (false);
	}
	ft_putstr_fd("-pipex error: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": command not found.\n", 2);
	return (true);
}

void	free_child(t_cmd *cmd1, t_cmd *cmd2, int exit_status)
{
	free_struct(cmd1);
	free_struct(cmd2);
	exit(exit_status);
}

void	free_child_error(t_cmd *cmd1, t_cmd *cmd2, int pipefd[2], int fd)
{
	perror("-child error");
	close(fd);
	close(pipefd[0]);
	close(pipefd[1]);
	free_child(cmd1, cmd2, EXIT_FAILURE);
}
