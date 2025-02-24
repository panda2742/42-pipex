/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:59:51 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/24 16:17:39 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_bool	_is_empty(const char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != ' ')
			return (false);
	}
	return (true);
}

char		**get_path(char **envp)
{
	char	**res;
	char	*env;
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 4) != 0)
			continue ;
		env = ft_substr(envp[i], 5, ft_strlen(envp[i]));
		if (!env)
			return (NULL);
		res = ft_split(envp[i], ':');
		free(env);
		if (!res)
			return (NULL);
		return (res);
	}
	return (NULL);
}

int	pipex(t_pipex *p, char **argv, char **envp)
{
	init_cmd(&p->cmd1);
	init_cmd(&p->cmd2);
	p->children_status[0] = true;
	p->children_status[1] = true;
	exec_cmd(p, argv, envp);
	if (p->children_status[0])
		clear_cmd(&p->cmd1);
	if (p->children_status[1])
		clear_cmd(&p->cmd2);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	int	pipex_result;

	if (argc != 5)
		return ((void)ft_putstr_fd("I expect 4 arguments: {infile} {cmd} {cmd} [outfile]\n", 2), EXIT_FAILURE);
	if (_is_empty(argv[2]) || _is_empty(argv[3]))
		return (EXIT_FAILURE);
	t_pipex	p;
	p.infile = open(argv[1], O_RDONLY);
	if (p.infile < 0)
		return ((void)perror(argv[1]), EXIT_FAILURE);
	p.outfile = open(argv[4], O_TRUNC | O_RDWR | O_CREAT, 00777);
	if (p.outfile < 0)
		return ((void)perror(argv[4]), EXIT_FAILURE);
	pipex_result = pipex(&p, argv, envp);
	close(p.infile);
	close(p.outfile);
	return (pipex_result);
}
