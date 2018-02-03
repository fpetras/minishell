/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 16:15:30 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/03 17:36:00 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(void)
{
	return ;
}

void	ft_setenv(void)
{
	return ;
}

void	ft_unsetenv(void)
{
	return ;
}

int		ft_check_commands(char **args, char **environ)
{
	if (ft_strequ("echo", args[0]))
		ft_echo(args);
	else if (ft_strequ("cd", args[0]))
		ft_cd();
	else if (ft_strequ("setenv", args[0]))
		ft_setenv();
	else if (ft_strequ("unsetenv", args[0]))
		ft_unsetenv();
	else if (ft_strequ("env", args[0]))
		ft_env(environ);
	else if (ft_strequ("exit", args[0]))
		return (-1);
	return (0);
}

char	*ft_tab_to_space(char *trimmed)
{
	int i;

	i = 0;
	while (trimmed[i])
	{
		if (trimmed[i] == '\t')
			trimmed[i] = ' ';
		i++;
	}
	return (trimmed);
}

int		ft_parse_input(char *input, char **environ)
{
	int		i;
	char	*trimmed;
	char	**args;

	i = 0;
	trimmed = ft_strtrim(input);
	if (ft_strlen(trimmed))
	{
		ft_tab_to_space(trimmed);
		args = ft_strsplit(trimmed, ' ');
		free(trimmed);
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

int		ft_read_input(char *input)
{
	int		i;
	int		ret;
	char	buf;

	i = 0;
	ret = 1;
	while (1)
	{
		ret = read(0, &buf, 1);
		if (ret <= 0)
		{
			ft_printf("\n");
			return (-1);
		}
		input[i] = buf;
		if (buf == '\n')
		{
			input[i] = '\0';
			return (1);
		}
		i++;
	}
}

char	**ft_create_environment(char **env)
{
	int		i;
	int		len;
	char	**environ;

	i = 0;
	len = 0;
	while (env[len])
		len++;
	environ = (char**)malloc(sizeof(char*) * (len + 1));
	while (env[i])
	{
		environ[i] = ft_strdup(env[i]);
		i++;
	}
	return (environ);
}

int		main(int ac, char **av, char **env)
{
	char	*input;
	char	**environ;

	(void)ac;
	(void)av;
	input = ft_strnew(1024);
	environ = ft_create_environment(env);
	ft_printf("$> ");
	while (1)
	{
		if (ft_read_input(input) <= 0)
			break ;
		if (ft_parse_input(input, environ) == -1)
			break ;
		free(input);
		input = ft_strnew(1024);
		ft_printf("$> ");
	}
	if (input)
		free(input);
	ft_free_tab(environ);
	return (0);
}
