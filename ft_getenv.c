/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 09:24:28 by fpetras           #+#    #+#             */
/*   Updated: 2018/03/03 13:02:02 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *var, char **environ)
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

int		ft_getenv_index(char *var, char **environ)
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
