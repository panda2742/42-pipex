/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:59:49 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/25 16:16:43 by ehosta           ###   ########.fr       */
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

void	exec_cmd(t_cmd *cmd1, t_cmd *cmd2, char **envp);
t_bool	check_empty(char *s);
void	free_struct(t_cmd *c);
void	free_child(t_cmd *cmd1, t_cmd *cmd2, int exit_status);
void	free_child_error(t_cmd *cmd1, t_cmd *cmd2, int pipefd[2], int fd);

#endif