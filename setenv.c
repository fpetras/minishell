/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 08:39:42 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/07 11:52:15 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define ERR1 "setenv: Too many arguments.\n"
#define ERR2 "setenv: Variable name must begin with a letter.\n"
#define ERR3 "setenv: Variable name must contain alphanumeric characters.\n"
#define ERR4 "setenv: Maximum number of environment variables exceeded.\n"

static int	ft_setenv_error(char **args)
{
	int ac;
	int i;

	ac = 0;
	i = 0;
	while (args[ac])
		ac++;
	if (ac > 3)
		return (ft_dprintf(2, ERR1));
	else if (!ft_isalpha(args[1][0]))
		return (ft_dprintf(2, ERR2));
	while (args[1][i])
	{
		if (!ft_isalnum(args[1][i]) && args[1][i] != '_')
			return (ft_dprintf(2, ERR3));
		i++;
	}
	return (0);
}

static void	ft_add_env_var(char **args, char **environ)
{
	int		len;
	char	*new_var;
	char	*tmp;

	len = 0;
	while (environ[len])
		len++;
	if (len > MAX_SETENV)
	{
		ft_dprintf(2, ERR4);
		return ;
	}
	new_var = ft_strjoin(args[1], "=");
	tmp = NULL;
	if (args[2])
		tmp = ft_strjoin(new_var, args[2]);
	if (tmp)
	{
		environ[len] = ft_strdup(tmp);
		free(tmp);
	}
	else
		environ[len] = ft_strdup(new_var);
	free(new_var);
}

static void	ft_modify_env_var(char **args, char **environ, int i)
{
	char *new_var;
	char *tmp;

	new_var = ft_strjoin(args[1], "=");
	tmp = NULL;
	if (args[2])
		tmp = ft_strjoin(new_var, args[2]);
	free(environ[i]);
	if (tmp)
	{
		environ[i] = ft_strdup(tmp);
		free(tmp);
	}
	else
		environ[i] = ft_strdup(new_var);
	free(new_var);
}

int			ft_setenv(char **args, char **environ)
{
	int i;

	i = 0;
	if (!args[1])
		return (ft_env(args, environ));
	else if (ft_setenv_error(args))
		return (-1);
	if ((i = ft_get_env_var_index(args[1], environ)) != -1)
		ft_modify_env_var(args, environ, i);
	else
		ft_add_env_var(args, environ);
	return (0);
}
