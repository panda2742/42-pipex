/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:31:22 by mlazzare          #+#    #+#             */
/*   Updated: 2025/02/25 10:18:07 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_struct(t_cmd *c)
{
	int	i;

	i = 0;
	if (c->cmd)
		free(c->cmd);
	ft_free_strtab(c->path);
	while (c->args[i])
		free(c->args[i++]);
}

t_bool	check_empty(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != ' ')
			return (false);
	}
	error_msg(s);
	return (true);
}

void	error_msg(char *c)
{
	ft_eprintf("-pipex error: %s: command not found.\n", c);
}

void	free_all(t_cmd *c, t_cmd *d)
{
	free_struct(c);
	free_struct(d);
}
