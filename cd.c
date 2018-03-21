/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 10:30:29 by fpetras           #+#    #+#             */
/*   Updated: 2018/03/03 13:03:14 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_modify_pwd_vars(char *path, char **environ, int i, int old)
{
	char *pwd;

	if (!old)
	{
		pwd = ft_strjoin("PWD=", path);
		free(environ[i]);
		environ[i] = ft_strdup(pwd);
		free(pwd);
	}
	else
	{
		pwd = ft_strjoin("OLDPWD=", path);
		free(environ[i]);
		environ[i] = ft_strdup(pwd);
		free(pwd);
	}
}

static int	ft_cd_error(char *str, char *new_dir, int p)
{
	if (p == 3)
		ft_dprintf(2, "cd: too many arguments\n");
	else if (p == 2 && !new_dir)
		ft_dprintf(2, "cd: string not in pwd: %s\n", str);
	else if (access(new_dir, F_OK) == -1)
		ft_dprintf(2, "cd: no such file or directory: %s\n", new_dir);
	else if (access(new_dir, R_OK) == -1)
		ft_dprintf(2, "cd: permission denied: %s\n", new_dir);
	else
		ft_dprintf(2, "cd: not a directory: %s\n", new_dir);
	if (p == 2)
		free(new_dir);
	return (-1);
}

static int	ft_replace_directory(char *new_dir, char *old_dir,
			char *search, char **environ)
{
	int		index;
	char	pwd[MAXPATHLEN];
	char	*home;

	if (chdir(new_dir) == -1)
		return (ft_cd_error(search, new_dir, 2));
	getcwd(pwd, MAXPATHLEN);
	if ((index = ft_getenv_index("PWD", environ)) != -1)
		ft_modify_pwd_vars(pwd, environ, index, 0);
	if ((index = ft_getenv_index("OLDPWD", environ)) != -1)
		ft_modify_pwd_vars(old_dir, environ, index, 1);
	if (!(home = ft_getenv("HOME", environ)))
		ft_printf("%s\n", pwd);
	else
	{
		if (ft_strequ(home, pwd))
			ft_printf("~\n");
		else if (ft_strncmp(home, pwd, ft_strlen(home)) == 0)
			ft_printf("~%s\n", &pwd[ft_strlen(home)]);
		else
			ft_printf("%s\n", pwd);
	}
	free(new_dir);
	return (0);
}

static int	ft_change_directory(char *new_dir, char *old_dir,
			char **environ, int p)
{
	int		index;
	char	pwd[MAXPATHLEN];
	char	*home;

	if (chdir(new_dir) == -1)
		return (ft_cd_error(NULL, new_dir, p));
	getcwd(pwd, MAXPATHLEN);
	if ((index = ft_getenv_index("PWD", environ)) != -1)
		ft_modify_pwd_vars(pwd, environ, index, 0);
	if ((index = ft_getenv_index("OLDPWD", environ)) != -1)
		ft_modify_pwd_vars(old_dir, environ, index, 1);
	if (p && (!(home = ft_getenv("HOME", environ))))
		ft_printf("%s\n", pwd);
	else if (p)
	{
		if (ft_strequ(home, pwd))
			ft_printf("~\n");
		else if (ft_strncmp(home, pwd, ft_strlen(home)) == 0)
			ft_printf("~%s\n", &pwd[ft_strlen(home)]);
		else
			ft_printf("%s\n", pwd);
	}
	return (0);
}

#define R_D ft_replace_directory
#define S_R ft_strreplace

int			ft_cd(char **args, char **environ)
{
	int		i;
	int		ac;
	char	pwd[MAXPATHLEN];
	char	*home;
	char	*oldpwd;

	i = 1;
	ac = 0;
	while (args[ac])
		ac++;
	getcwd(pwd, MAXPATHLEN);
	home = ft_getenv("HOME", environ);
	oldpwd = ft_getenv("OLDPWD", environ);
	if (!args[1] || (ft_strequ("--", args[1]) && !args[2]))
		return (ft_change_directory(home, pwd, environ, 0));
	if (ft_strequ("--", args[i]))
		i++;
	if (ac - i >= 3)
		return (ft_cd_error(NULL, NULL, 3));
	if (ft_strequ("-", args[i]) && !args[i + 1])
		return (ft_change_directory(oldpwd, pwd, environ, 1));
	if (args[i] && args[i + 1])
		return (R_D(S_R(args[i], args[i + 1], pwd), pwd, args[i], environ));
	return (ft_change_directory(args[i], pwd, environ, 0));
}
