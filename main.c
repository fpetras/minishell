/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 16:15:30 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/02 12:02:13 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_parse_input(char *input)
{
	int		i;
	char	*trimmed;
	char	**args;

	i = 0;
	trimmed = ft_strtrim(input);
	free(input);
	if (ft_strlen(trimmed))
	{
		ft_tab_to_space(trimmed);
		args = ft_strsplit(trimmed, ' ');
		i = 0;
		while (args[i])
		{
			ft_printf("%s\n", args[i]);
			free(args[i]);
			i++;
		}
		free(args);
	}
	free(trimmed);
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
			ft_printf("^D\n");
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

int		main(int ac, char **av, char **env)
{
	int		ret;
	char	*input;

	(void)ac;
	(void)av;
	(void)env;
	ret = 1;
	input = ft_strnew(1024);
	ft_printf("$> ");
	while (1)
	{
		ret = ft_read_input(input);
		if (ret <= 0)
			break ;
		ft_parse_input(input);
		input = ft_strnew(1024);
		ft_printf("$> ");
	}
	if (input)
		free(input);
	return (0);
}
