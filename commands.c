/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 18:25:00 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/06 19:14:21 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_unsetenv(void)
{
	return ;
}

static int	ft_check_commands(char **args, char **environ)
{
	if (ft_strequ("echo", args[0]))
		ft_echo(args);
	else if (ft_strequ("cd", args[0]))
		ft_cd(args, environ);
	else if (ft_strequ("setenv", args[0]))
		ft_setenv(args, environ);
	else if (ft_strequ("unsetenv", args[0]))
		ft_unsetenv();
	else if (ft_strequ("env", args[0]))
		ft_env(args, environ);
	else if (ft_strequ("exit", args[0]))
		return (-1);
	else if (ft_path_executables(args, environ))
		;
	else if (ft_executables(args, environ))
		;
	else if (args[0][0] == '.' && args[0][1] == '/' && ft_is_file(args[0]))
		ft_dprintf(2, "%s: permission denied\n", args[0]);
	else if (ft_strchr(args[0], '/'))
		ft_dprintf(2, "%s: no such file or directory\n", args[0]);
	else
		ft_dprintf(2, "%s: command not found\n", args[0]);
	return (0);
}

int			ft_multiple_commands(char *input, char **environ)
{
	int		i;
	char	*trimmed;
	char	**commands;
	char	**args;

	i = -1;
	commands = ft_strsplit(input, ';');
	while (commands[++i])
	{
		trimmed = ft_strtrim(commands[i]);
		if (ft_strlen(trimmed))
		{
			ft_tab_to_space(trimmed);
			args = ft_strsplit(trimmed, ' ');
			free(trimmed);
			ft_expansions(args, environ);
			if (ft_check_commands(args, environ) == -1)
				return (ft_free_tabs2(commands, args));
			ft_free_tab(args);
		}
		else
			free(trimmed);
	}
	ft_free_tab(commands);
	return (0);
}

int			ft_single_command(char *input, char **environ)
{
	char *trimmed;
	char **args;

	trimmed = ft_strtrim(input);
	if (ft_strlen(trimmed))
	{
		ft_tab_to_space(trimmed);
		args = ft_strsplit(trimmed, ' ');
		free(trimmed);
		ft_expansions(args, environ);
		if (ft_check_commands(args, environ) == -1)
		{
			ft_free_tab(args);
			return (-1);
		}
		ft_free_tab(args);
	}
	else
		free(trimmed);
	return (0);
}
