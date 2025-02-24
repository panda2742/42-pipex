/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:00:52 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/24 16:17:25 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_one(t_pipex *p, char **argv, char **envp)
{
	int		i;

	if (!get_cmd(envp, &p->cmd1, argv[2]) || !check_cmd(&p->cmd1))
	{
		close(p->infile);
		p->children_status[0] = false;
		return ((void)clear_cmd(&p->cmd1));
	}
	i = -1;
	if (!p->cmd1.valid_path)
		exit(EXIT_FAILURE);
	p->cmd1.args[p->cmd1.argc] = 0;
	if (dup2(p->infile, STDIN_FILENO) < 0
		|| dup2(p->pipes[1], STDOUT_FILENO) < 0)
		return (perror("Child one"));
	close(p->pipes[0]);
	close(p->pipes[1]);
	close(p->infile);
	close(p->outfile);
	execve(p->cmd1.valid_path, p->cmd1.args, NULL);
}

void	child_two(t_pipex *p, char **argv, char **envp)
{
	int		i;

	if (!get_cmd(envp, &p->cmd2, argv[3]) || !check_cmd(&p->cmd2))
	{
		close(p->outfile);
		p->children_status[1] = false;
		return ((void)clear_cmd(&p->cmd2));
	}
	i = -1;
	if (!p->cmd2.valid_path)
		exit(EXIT_FAILURE);
	p->cmd2.args[p->cmd2.argc] = 0;
	if (dup2(p->outfile, STDOUT_FILENO) < 0
		|| dup2(p->pipes[0], STDIN_FILENO) < 0)
		return (perror("Child two"));
	close(p->pipes[0]);
	close(p->pipes[1]);
	close(p->infile);
	close(p->outfile);
	execve(p->cmd2.valid_path, p->cmd2.args, NULL);
}
