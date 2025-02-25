/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:35:14 by mlazzare          #+#    #+#             */
/*   Updated: 2025/02/25 14:29:14 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_cmd(t_cmd *c, int f)
{
	c->f = f;
	c->path = 0;
	c->cmd = 0;
	c->args[0] = 0;
}

static char	**get_path(char **envp)
{
	char	**res;
	char	*env;
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", PATH))
		{
			env = ft_substr(envp[i], START, ft_strlen(envp[i]));
			if (!env)
				return (NULL);
			res = ft_split(env, ':');
			free(env);
			return (res);
		}
	}
	return (NULL);
}

static int	get_cmd(char **envp, t_cmd *c, char *cmd)
{
	int		i;
	char	**tmp;

	i = -1;
	c->path = get_path(envp);
	if (!c->path)
		return (0);
	tmp = ft_split(cmd, ' ');
	if (!tmp)
		return (0);
	c->cmd = ft_substr(tmp[i + 1], 0, ft_strlen(tmp[i + 1]));
	if (!c->cmd)
		return (ft_free_strtab(tmp), 0);
	while (tmp[++i])
	{
		c->args[i] = ft_substr(tmp[i], 0, ft_strlen(tmp[i]));
		if (!c->args[i])
		{
			ft_free_strtab(c->args);
			return (ft_free_strtab(tmp), 0);
		}
	}
	c->args[i] = 0;
	ft_free_strtab(tmp);
	return (1);
}

int	main(int ac, char **ag, char **envp)
{
	int		f1;
	int		f2;
	t_cmd	cmd1;
	t_cmd	cmd2;

	if (ac != 5)
		return (ft_putstr_fd("Invalid number of arguments.", 2));
	if (check_empty(ag[2]) || check_empty(ag[3]))
		return (1);
	f1 = open(ag[1], O_RDONLY);
	f2 = open(ag[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f1 < 0)
		return (perror("-pipex error (infile)"), EXIT_FAILURE);
	if (f2 < 0)
		return (perror("-pipex error (outfile)"), EXIT_FAILURE);
	init_cmd(&cmd1, f1);
	init_cmd(&cmd2, f2);
	get_cmd(envp, &cmd1, ag[2]);
	get_cmd(envp, &cmd2, ag[3]);
	exec_cmd(&cmd1, &cmd2, envp);
	free_struct(&cmd1);
	free_struct(&cmd2);
	if (close(f1) < 0 || close(f2) < 0)
		return (ft_putstr_fd(strerror(errno), 2));
	return (0);
}
