/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:59:49 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/24 16:16:05 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	char	*cmd;
	char	**path;
	char	*valid_path;
	char	*args[1024];
	int		argc;
}			t_cmd;

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		pipes[2];
	int		status;
	pid_t	p1;
	pid_t	p2;
	t_bool	children_status[2];
	t_cmd	cmd1;
	t_cmd	cmd2;
}			t_pipex;

void	init_cmd(t_cmd *cmd);
void	clear_cmd(t_cmd *cmd);
void	exec_cmd(t_pipex *p, char **argv, char **envp);
t_bool	check_cmd(t_cmd *cmd);
t_bool	get_cmd(char **envp, t_cmd *cmd, char *cmd_name);

void	child_one(t_pipex *p, char **argv, char **envp);
void	child_two(t_pipex *p, char **argv, char **envp);

char	**get_path(char **envp);

#endif