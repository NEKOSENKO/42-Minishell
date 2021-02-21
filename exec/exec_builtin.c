#include "../minishell.h"

int		exec_builtin(char **cmd, int ret)
{
	if (ret == 1)
		ft_echo(cmd);
	else if (ret == 2)
		ft_cd(cmd);
	else if (ret == 3)
		ft_pwd();
	else if (ret == 4)
		ft_export();
	else if (ret == 5)
		printf("hello from unset\n");
	else if (ret == 6)
		ft_env(cmd);
	else if (ret == 7)
		ft_exit(cmd);
	return (0);
}