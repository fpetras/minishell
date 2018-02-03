/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 15:31:07 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/03 15:31:26 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(char **args)
{
	int i;
	int n;

	i = 1;
	n = 0;
	if (!args[1])
	{
		ft_printf("\n");
		return (0);
	}
	while (ft_strequ("-n", args[i]))
	{
		i++;
		n = 1;
	}
	if (ft_strequ("-", args[i]))
		i++;
	while (args[i])
	{
		ft_printf("%s", args[i]);
		args[i + 1] ? ft_printf(" ") : 0;
		i++;
	}
	!n ? ft_printf("\n") : 0;
	return (0);
}
