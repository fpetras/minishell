/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 11:32:42 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/07 09:04:35 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_pathjoin(char *path, char *command)
{
	char *tmp;
	char *joined;

	tmp = ft_strjoin(path, "/");
	joined = ft_strjoin(tmp, command);
	free(tmp);
	return (joined);
}

int			ft_path_executables(char **args, char **environ, int i)
{
	char		*executable;
	char		**paths;
	struct stat	buf;
	pid_t		pid;

	if (!(paths = ft_strsplit(ft_get_env_var("PATH", environ), ':')))
		return (0);
	while (paths[++i])
	{
		executable = ft_pathjoin(paths[i], args[0]);
		if (lstat(executable, &buf) == 0)
			if (S_ISREG(buf.st_mode) && S_IXUSR & buf.st_mode)
			{
				if ((pid = fork()) == 0)
					execve(executable, args, environ);
				wait(&pid);
				ft_free_tab(paths);
				free(executable);
				return (1);
			}
		free(executable);
	}
	ft_free_tab(paths);
	return (0);
}

int			ft_executables(char **args, char **environ)
{
	struct stat	buf;
	pid_t		pid;

	if (lstat(args[0], &buf) == 0)
	{
		if (S_ISREG(buf.st_mode) && S_IXUSR & buf.st_mode)
		{
			pid = fork();
			if (pid == 0)
				execve(args[0], args, environ);
			wait(&pid);
			return (1);
		}
	}
	return (0);
}
