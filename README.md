# Minishell

A mini UNIX command-line interpreter.

## Installation:

`git clone --recurse-submodules https://github.com/fpetras/minishell.git && cd minishell && make`

## Usage:

`usage: ./minishell`

Minishell features:

 - Execution of commands in the directories specified in the `$PATH` environment variable
 - Separation of commands with ;
 - Tilde and variable expansion
 - A series of builtins
 
### Builtins:

- **echo** -- write arguments to the standard output
    * `echo [-n] [string ...]`\
      Writes each operand, separated by a space, to the standard output. If the *-n* flag is not present, prints a newline at the end.
      
 - **cd** -- change the working directory
    * `cd [directory]`
    * `cd old new`\
      In the first form, changes to *directory*, or to the value of $HOME if *directory* is not specified. If *directory* is `-`, changes to the previous directory.\
      The second form of *cd* substitutes the string *new* for the string *old* in the name of the current directory, and tries to change to this new directory. 
      
 - **setenv** -- change or add an environment variable
    * `setenv [name [value]`\
      Adds the variable *name* to the environment with the value *value*, if *name* does not already exist. If *name* does exist, its value is changed to *value*.\
      If no name is present, *setenv* prints the environment.
      
 - **unsetenv** -- remove an environment variable
    * `unsetenv name`\
      Removes an environment variable. If the named variable does not exist, the environment is left unchanged.
      
 - **env** -- print the environment
    * `env`\
      Prints out the names and values of the variables in the environment, with one name/value pair per line.\
      Any attempt to execute another utility after modifying the environment will invoke /usr/bin/env.
      
 - **exit** -- exit the shell
    * `exit`\
      Exits the shell.

### In action:

![GIF](http://g.recordit.co/pY8JC2dq2N.gif)

## Code snippets:

Main function:

```C
int         main(int ac, char **av, char **env)
{
    char    *input;
    char    **environ;

    (void)ac;
    (void)av;
    input = ft_strnew(MAX_CANON);
    environ = ft_create_environment(input, env);
    if (!input || !environ)
        return (-1);
    ft_printf("$> ");
    while (1)
    {
        if (ft_read_input(input) <= 0)
            break ;
        if (ft_parse_input(input, environ) == -1)
            break ;
        free(input);
        input = ft_strnew(MAX_CANON);
        ft_printf("$> ");
    }
    if (input)
        free(input);
    ft_free_tab(environ);
    return (0);
}
```

Part of builtin cd:

```C
static int  ft_change_directory(char *new_dir, char *old_dir,
            char **environ, int p)
{
    int     index;
    char    pwd[MAXPATHLEN];
    char    *home;

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
```

## [Subject](https://github.com/fpetras/42-subjects/blob/master/minishell.en.pdf "minishell.en.pdf")
