/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 07:39:35 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/06 18:29:20 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "libft/get_next_line/get_next_line.h"
# include "libft/ft_printf/ft_printf.h"

# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <dirent.h>
# include <sys/param.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

int		ft_single_command(char *input, char **environ);
int		ft_multiple_commands(char *input, char **environ);
int		ft_check_commands(char **args, char **environ);
int		ft_echo(char **args);
int		ft_cd(char **args, char **environ);
int		ft_setenv(char **args, char **environ);
int		ft_env(char **args, char **environ);
int		ft_path_executables(char **args, char **environ);
int		ft_executables(char **args, char **environ);
int		ft_get_env_var_index(char *name, char **environ);
char	*ft_get_env_var(char *name, char **environ);
char	*ft_strreplace(char *search, char *replace, char *subject);
char	*ft_tab_to_space(char *trimmed);
char	**ft_expansions(char **args, char **environ);
int		ft_is_file(char *arg);
int		ft_free_tabs2(char **commands, char **args);
void	ft_free_tab(char **tab);

#endif
