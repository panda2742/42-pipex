/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:59:49 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/25 10:41:50 by ehosta           ###   ########.fr       */
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

# define PATH 5
# define START 6

typedef struct s_cmd
{
	char	*cmd;
	char	**path;
	char	*args[100];
	int		f;
}	t_cmd;

void	pipex(int f1, int f2, char **ag, char **ep);
void	exec_cmd(t_cmd *cmd1, t_cmd *cmd2, char **envp);
void	error_msg(char *c);
int		check_cmd(t_cmd *c);
t_bool	check_empty(char *s);

char	*get_full_path(char *path, char *cmd_name);

void	free_struct(t_cmd *c);
void	free_all(t_cmd *c, t_cmd *d);

#endif