/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 10:05:44 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/06 10:07:19 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_is_file(char *arg)
{
	struct stat buf;

	if (lstat(arg, &buf) == -1)
		return (0);
	else if (S_ISREG(buf.st_mode))
		return (1);
	else if (S_ISDIR(buf.st_mode))
		return (2);
	else if (S_ISLNK(buf.st_mode))
		return (3);
	else if (S_ISSOCK(buf.st_mode))
		return (4);
	else if (S_ISBLK(buf.st_mode))
		return (5);
	else if (S_ISWHT(buf.st_mode))
		return (6);
	else if (S_ISCHR(buf.st_mode))
		return (7);
	else if (S_ISFIFO(buf.st_mode))
		return (8);
	else
		return (9);
}
