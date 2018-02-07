/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 09:24:28 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/07 08:17:20 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env_var(char *var, char **environ)
{
	int i;
	int j;

	i = 0;
	while (environ[i])
	{
		j = 0;
		while (environ[i][j] == var[j] && environ[i][j] != '=')
			j++;
		if (environ[i][j] == '=' && j == (int)ft_strlen(var))
			return (&environ[i][j + 1]);
		i++;
	}
	return (NULL);
}

int		ft_get_env_var_index(char *var, char **environ)
{
	int i;
	int j;

	i = 0;
	while (environ[i])
	{
		j = 0;
		while (environ[i][j] == var[j] && environ[i][j] != '=')
			j++;
		if (environ[i][j] == '=' && j == (int)ft_strlen(var))
			return (i);
		i++;
	}
	return (-1);
}
