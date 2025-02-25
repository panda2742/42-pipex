/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:48:02 by mlazzare          #+#    #+#             */
/*   Updated: 2025/02/25 16:18:54 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	_child_one(int *pipefd, t_cmd *c, char **envp, t_cmd *outc);
static void	_child_two(int *pipefd, t_cmd *c, char **envp, t_cmd *inc);
static char	*_get_full_path(char *path, char *cmd_name);

void	exec_cmd(t_cmd *cmd1, t_cmd *cmd2, char **envp)
{
	int		status;
	int		pipefd[2];
	pid_t	p1;
	pid_t	p2;

	status = 0;
	pipe(pipefd);
	p1 = fork();
	if (p1 == 0)
		_child_one(pipefd, cmd1, envp, cmd2);
	p1 = -1;
	p2 = fork();
	if (p2 == 0)
		_child_two(pipefd, cmd2, envp, cmd1);
	p2 = -1;
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
	close(pipefd[1]);
}

static void	_child_one(int *pipefd, t_cmd *c, char **envp, t_cmd *outc)
{
	int		i;
	char	*cmd;

	i = -1;
	if (dup2(c->f, STDIN_FILENO) < 0
		|| dup2(pipefd[1], STDOUT_FILENO) < 0)
		return (free_child_error(c, outc, pipefd, outc->f));
	close(pipefd[0]);
	close(pipefd[1]);
	close(c->f);
	close(outc->f);
	while (c->path[++i])
	{
		cmd = _get_full_path(c->path[i], c->cmd);
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
	return (free_child(c, outc, EXIT_FAILURE));
}

static void	_child_two(int *pipefd, t_cmd *c, char **envp, t_cmd *inc)
{
	int		i;
	char	*cmd;

	i = -1;
	if (dup2(c->f, STDOUT_FILENO) < 0
		|| dup2(pipefd[0], STDIN_FILENO) < 0)
		return (free_child_error(c, inc, pipefd, inc->f));
	close(pipefd[0]);
	close(pipefd[1]);
	close(c->f);
	close(inc->f);
	while (c->path[++i])
	{
		cmd = _get_full_path(c->path[i], c->cmd);
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
	return (free_child(c, inc, EXIT_FAILURE));
}

static char	*_get_full_path(char *path, char *cmd_name)
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
