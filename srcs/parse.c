#include "../minishell.h"

int		skip_spaces(const char *s)
{
	int i;

	i = 0;
	while(s[i] == ' ')
		i++;
	return (i);
}

int		gn_word(const char *str, char *d)
{
	int		i;
	char	quote[2];
	
	i = skip_spaces(str);
	ft_bzero(quote, 2);
	while (str[i])
	{
		if (!quote[0] || is_on_char(str, i, quote))
		{
			if (is_on_char(str, i, "'\""))
				quote[0] = quote[0] ? 0 : str[i];
			if (!is_on_char(str, i , d) || is_on_char(str, i, d))
				break;
		}
		i++;
	}
	i += skip_spaces(str + i);
	return (i);
}

int		proc_command(char *str)
{
	t_command *com;

	com = g_minishell.com_tail->content;
	if (((ft_strncmp(str,">", 1) == 0 ||
	ft_strncmp(str,">>", 2) == 0 ||
	ft_strncmp(str, "<", 1) == 0) && 
	(g_minishell.read_next != NULL && 
	!senko_equal_str(g_minishell.read_next, "|"))) ||
	((ft_strncmp(str, "|" , 1) == 0 ||
	ft_strncmp(str, ";", 1) == 0) 
	&& (g_minishell.read_next != NULL ||
	(com->argv == NULL && com->red_files == NULL))))
		return (err_syntax(str));
	if (ft_strncmp(str, "|", 1) == 0)
		parse_pipe(str);
	else if (ft_strncmp(str, ";", 1) == 0)
		parse_semi_col(str);
	else if (ft_strncmp(str, "<", 1) == 0)
		parse_input_red(str);
	else if (ft_strncmp(str, ">>", 2) == 0)
		parse_output_red(str,">>");
	else if (ft_strncmp(str, ">", 1) == 0)
		parse_output_red(str, ">");
	else
		parse_command(str);

		// //printf("test : %s\n", str);
		// while (com->argv)
		// {
		// 	printf("token : %s\n", com->argv->content);
		// 	com->argv = com->argv->next;
		// }

		// while (com->red_files)
		// {
		// 	printf("red : %s\n", com->red_files->content);
		// 	com->red_files = com->red_files->next;
		// }
	return (0);
}

void shell_parse()
{
	int len;

	while (g_minishell.status && g_minishell.input[g_minishell.pos]
	&& (g_minishell.pos += gn_word(g_minishell.input + g_minishell.pos, SEP)) != -1)
	{
		if (g_minishell.input[g_minishell.pos] == 0)
			break;
		len = word_len(g_minishell.input + 
		g_minishell.pos, SEP,0);
		proc_command(g_minishell.input + g_minishell.pos);
		g_minishell.pos += len;
	}
}