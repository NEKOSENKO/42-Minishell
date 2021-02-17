#include "minishell.h"

void	com_initiate()
{
	g_minishell.com_head = ft_lstnew(new_command(0, 1, -1));
	g_minishell.com_tail = g_minishell.com_head;
	g_minishell.status = 1;
	g_minishell.fork_p = 0;
	g_minishell.read_next = NULL;
	g_minishell.pos = 0;
}

char	*read_line()
{
	char	buf;
	int		ret;

	g_minishell.input = ft_strdup("");
	while ((ret = read(0, &buf, 1)) != -1)
	{
		if (ret == 0)
		{
			if (ft_strncmp(g_minishell.input, "", 1) == 0)
			{
				if (!senko_equal_str(g_minishell.read_next, "|"))
					senko_exit(NULL);
				err_syntax("\x4");
				break ;
			}
			ft_putstr_fd("  \b\b", 1);
			continue;
		}
		else if (buf == '\n')
			break;
		g_minishell.input = ft_strappend(g_minishell.input, buf);
	}
	return (g_minishell.input);
}

void	shell_exec(int n)
{
	if (g_minishell.status && g_minishell.read_next != NULL)
		err_syntax("\n");
	if (g_minishell.status && g_minishell.read_next == NULL)
		printf(""); // execute here
	if (!senko_equal_str(g_minishell.read_next, "|"))
		ft_lstclear(&g_minishell.com_head, free_com);
	if (n)
	{
		free(g_minishell.input);
		g_minishell.input = NULL;
	}
}

void	shell_init(char **env)
{
	char	*cwd;

	g_env.env_h = array_to_list(env);
	cwd = getcwd(NULL, 0);
	add_element("PWD", cwd);
	free(cwd);
	add_element("SHLVL", "1");
	//SIGNALS INT & QUIT
	//handle signals init here
	g_minishell.ret = 0;
}

int main(int ac, char **av, char **ev)
{
	char *old_com;

	shell_init(ev);
	av = NULL;
	ac = 0;
	while (1)
	{
	
		prompt(NULL);
		com_initiate();
		g_minishell.input = read_line();
		while (end_pipe())
		{
			prompt("|");
			g_minishell.fork_p = 0;
			old_com = g_minishell.input;
			g_minishell.input = read_line();
			free(old_com);
		}
		shell_parse();
		shell_exec(1);
	}
	return (g_minishell.ret);
}