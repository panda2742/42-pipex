/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:06:11 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/24 16:17:08 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_cmd(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->path = NULL;
	cmd->args[0] = NULL;
	cmd->argc = 0;
	cmd->valid_path = NULL;
}

void	clear_cmd(t_cmd *cmd)
{
	int	i;

	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->path)
		ft_free_strtab(cmd->path);
	if (cmd->args[0])
	{
		i = -1;
		while (++i < cmd->argc)
			free(cmd->args[i]);
	}
	if (cmd->valid_path)
		free(cmd->valid_path);
}

t_bool	check_cmd(t_cmd *cmd)
{
	int		i;
	char	*cmd_name;
	char	*tmp;

	i = -1;
	while (cmd->path[++i])
	{
		tmp = ft_strjoin(cmd->path[i], "/");
		cmd_name = ft_strjoin(tmp, cmd->cmd);
		free(tmp);
		if (!cmd_name)
			return (false);
		if (access(cmd_name, X_OK) != -1)
		{
			cmd->valid_path = cmd_name;
			return (true);
		}
		free(cmd_name);
	}
	ft_putstr_fd("Command not found.\n", 2);
	return (false);
}

void	exec_cmd(t_pipex *p, char **argv, char **envp)
{
	if (pipe(p->pipes) == -1)
		return (perror("Pipe error"));
	p->p1 = fork();
	if (p->p1 < 0)
		return (perror("Fork one failed"));
	if (p->p1 == 0)
		child_one(p, argv, envp);
	p->p2 = fork();
	if (p->p2 < 0)
		return (perror("Fork two failed"));
	if (p->p2 == 0)
		child_two(p, argv, envp);
	waitpid(-1, &p->status, 0);
	waitpid(-1, &p->status, 0);
	close(p->pipes[0]);
	close(p->pipes[1]);
	if (p->children_status[0])
		close(p->infile);
	if (p->children_status[1])
		close(p->outfile);
}

t_bool	get_cmd(char **envp, t_cmd *cmd, char *cmd_name)
{
	int		i;
	char	**tmp;

	i = -1;
	cmd->path = get_path(envp);
	if (!cmd->path)
		return (false);
	tmp = ft_split(cmd_name, ' ');
	if (!tmp)
		return (false);
	cmd->cmd = ft_substr(tmp[i + 1], 0, ft_strlen(tmp[i + 1]));
	if (!cmd->cmd)
		return (ft_free_strtab(tmp), false);
	while (tmp[++i])
	{
		cmd->args[i] = ft_substr(tmp[i], 0, ft_strlen(tmp[i]));
		if (!cmd->args[i])
			return (ft_free_strtab(cmd->args), ft_free_strtab(tmp), false);
		cmd->argc = i + 1;
	}
	cmd->args[i] = 0;
	ft_free_strtab(tmp);
	return (true);
}
