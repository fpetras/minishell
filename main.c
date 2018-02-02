#include "minishell.h"

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	int		i;
	int		ret;
	char	buf;
	char	*input;

	i = 0;
	ret = 1;
	input = ft_strnew(1024);
	ft_printf("$> ");
	while (1)
	{
		ret = read(0, &buf, 1);
		if (ret <= 0)
		{
			ft_printf("^D\n");
			break ;
		}
		input[i] = buf;
		if (buf == '\n')
		{
			input[i] = '\0';
			if (ft_strequ(input, "exit"))
				break ;
			if (ft_strlen(input))
				ft_printf("%s\n", input);
			ft_printf("$> ");
			free(input);
			input = ft_strnew(1024);
			i = -1;
		}
		i++;
	}
	if (input)
		free(input);
	return (0);
}
