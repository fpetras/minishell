/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 11:20:27 by fpetras           #+#    #+#             */
/*   Updated: 2018/03/03 13:04:15 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_tab_to_space(char *trimmed)
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

static char	**ft_dollar_to_env_var(char **args, char **environ)
{
	int		i;
	char	*var;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$' && ft_strlen(args[i]) > 1)
		{
			if ((var = ft_getenv(&args[i][1], environ)))
			{
				free(args[i]);
				args[i] = ft_strdup(var);
			}
			else
				args[i][0] = '\0';
		}
		i++;
	}
	return (args);
}

static char	**ft_tilde_to_home(char **args, char **environ)
{
	int		i;
	char	*home;
	char	*tmp;

	i = 0;
	if (!(home = ft_getenv("HOME", environ)))
		home = "\0";
	while (args[i])
	{
		if (ft_strequ("~", args[i]))
		{
			free(args[i]);
			args[i] = ft_strdup(home);
		}
		else if (args[i][0] == '~')
		{
			tmp = ft_strjoin(home, &args[i][1]);
			free(args[i]);
			args[i] = ft_strdup(tmp);
			free(tmp);
		}
		i++;
	}
	return (args);
}

char		**ft_expansions(char **args, char **environ)
{
	ft_tilde_to_home(args, environ);
	ft_dollar_to_env_var(args, environ);
	return (args);
}
