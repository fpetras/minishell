/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 07:14:07 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/07 08:20:56 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_remove_env_var(char **environ, int i)
{
	free(environ[i]);
	environ[i] = NULL;
	while (environ[i + 1])
	{
		environ[i] = ft_strdup(environ[i + 1]);
		free(environ[i + 1]);
		i++;
	}
	environ[i] = NULL;
}

int		ft_unsetenv(char **args, char **environ)
{
	int i;

	i = 0;
	if (!args[1])
	{
		ft_dprintf(2, "unsetenv: Too few arguments.\n");
		return (-1);
	}
	else if ((i = ft_get_env_var_index(args[1], environ)) != -1)
		ft_remove_env_var(environ, i);
	return (0);
}
