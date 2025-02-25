/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:48:02 by mlazzare          #+#    #+#             */
/*   Updated: 2025/02/25 14:29:50 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_one(int *pipefd, t_cmd *c, char **envp, int outfd)
{
	int		i;
	char	*cmd;

	i = -1;
	if (dup2(c->f, STDIN_FILENO) < 0
		|| dup2(pipefd[1], STDOUT_FILENO) < 0)
		return (perror("Child one"));
	close(pipefd[0]);
	close(pipefd[1]);
	close(c->f);
	close(outfd);
	while (c->path[++i])
	{
		cmd = get_full_path(c->path[i], c->cmd);
		if (!cmd)
			return ;
		if (access(cmd, X_OK) == 0 && execve(cmd, c->args, envp) != -1)
		{
			free(cmd);
			exit(EXIT_SUCCESS);
		}
		free(cmd);
	}
	perror("-child 1");
	exit(EXIT_FAILURE);
}

static void	child_two(int *pipefd, t_cmd *c, char **envp, int infd)
{
	int		i;
	char	*cmd;

	i = -1;
	if (dup2(c->f, STDOUT_FILENO) < 0
		|| dup2(pipefd[0], STDIN_FILENO) < 0)
		return (perror("Child two"));
	close(pipefd[0]);
	close(pipefd[1]);
	close(c->f);
	close(infd);
	while (c->path[++i])
	{
		cmd = get_full_path(c->path[i], c->cmd);
		if (!cmd)
			return ;
		if (access(cmd, X_OK) == 0 && execve(cmd, c->args, envp) != -1)
		{
			free(cmd);
			exit(EXIT_SUCCESS);
		}
		free(cmd);
	}
	perror("-child 2");
	exit(EXIT_FAILURE);
}

void	exec_cmd(t_cmd *cmd1, t_cmd *cmd2, char **envp)
{
	int		status;
	int		pipefd[2];
	pid_t	p1;
	pid_t	p2;

	status = 0;
	pipe(pipefd);
	p1 = fork();
	if (p1 < 0)
		return (perror("Fork one"));
	if (!p1)
		child_one(pipefd, cmd1, envp, cmd2->f);
	p2 = fork();
	if (p2 < 0)
		return (perror("Fork two"));
	if (!p2)
		child_two(pipefd, cmd2, envp, cmd1->f);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
	close(pipefd[1]);
}

char	*get_full_path(char *path, char *cmd_name)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin("/", path);
	tmp2 = ft_strjoin(tmp, "/");
	free(tmp);
	tmp = ft_strjoin(tmp2, cmd_name);
	free(tmp2);
	return (tmp);
}
