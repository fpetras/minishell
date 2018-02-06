/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 16:15:30 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/06 18:32:13 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_parse_input(char *input, char **environ)
{
	if (ft_strchr(input, ';'))
		return (ft_multiple_commands(input, environ));
	else
		return (ft_single_command(input, environ));
	return (0);
}

static int	ft_read_input(char *input)
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

static char	**ft_create_environment(char **env)
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

int			main(int ac, char **av, char **env)
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
