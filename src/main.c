/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:35:14 by mlazzare          #+#    #+#             */
/*   Updated: 2025/02/25 16:24:26 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	_get_cmd(char **envp, t_cmd *c, char *cmd);
static void	_init_cmd(t_cmd *c, int f);
static char	**_get_path(char **envp);
static int	_get_cmd_return(char **tmp);

int	main(int argc, char **argv, char **envp)
{
	int		f1;
	int		f2;
	t_cmd	cmd1;
	t_cmd	cmd2;

	if (argc != 5)
		return (ft_putstr_fd("Invalid number of arguments.\n", 2));
	if (check_empty(argv[2]) || check_empty(argv[3]))
		return (1);
	f1 = open(argv[1], O_RDONLY);
	f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	_init_cmd(&cmd1, f1);
	_init_cmd(&cmd2, f2);
	_get_cmd(envp, &cmd1, argv[2]);
	_get_cmd(envp, &cmd2, argv[3]);
	exec_cmd(&cmd1, &cmd2, envp);
	free_struct(&cmd1);
	free_struct(&cmd2);
	close(f1);
	close(f2);
	return (EXIT_SUCCESS);
}

static int	_get_cmd(char **envp, t_cmd *c, char *cmd)
{
	int		i;
	char	**tmp;

	i = -1;
	c->path = _get_path(envp);
	if (!c->path)
		return (0);
	tmp = ft_split(cmd, ' ');
	if (!tmp)
		return (0);
	c->cmd = ft_substr(tmp[i + 1], 0, ft_strlen(tmp[i + 1]));
	if (!c->cmd)
		return (_get_cmd_return(0));
	while (tmp[++i])
	{
		c->args[i] = ft_substr(tmp[i], 0, ft_strlen(tmp[i]));
		if (!c->args[i])
		{
			ft_free_strtab(c->args);
			return (_get_cmd_return(0));
		}
	}
	c->args[i] = 0;
	ft_free_strtab(tmp);
	return (1);
}

static int	_get_cmd_return(char **tmp)
{
	ft_free_strtab(tmp);
	return (0);
}

static void	_init_cmd(t_cmd *c, int f)
{
	c->f = f;
	c->path = 0;
	c->cmd = 0;
	c->args[0] = 0;
}

static char	**_get_path(char **envp)
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
