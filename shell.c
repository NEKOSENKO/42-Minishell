#include "shell.h"

/* this is here for norm shit 
void shell_loop(void)
{

}*/

char *read_line(void)
{
	int buff_size;
	int pos;
	int c;
	char *buffer;

	buff_size = 1024;
	pos = 0;
	buffer = malloc(sizeof(char) * buff_size);

	//protection 

	while (1)
	{
		c = senko_getchar();
		if (c == EOF || c == '\n')
		{
			buffer[pos] = '\0';
			return buffer;	
		}
		else 
			buffer[pos] = c;
		pos++;
		if (pos >= buff_size)
		{
			buff_size += 1024;
			buffer = malloc(sizeof(char) * buff_size);
			//protection
		}
	}

	return buffer;
}


int main(int ac, char **av, char **ev)
{
	t_env	*env;
	int 	ret;

	env = initiate(ac, av, ev);

	while (1) //Read-Eval-Print-L
	{
		ft_putstr("\033[1;3;4;33;41m Union_of_Senko_Shell_Republicans \033[0m$> ");
		env->input->line = read_line();
		if(!env)
			return -1;
		printf("  ~ initial buffer : > %s\n\n", env->input->line);
		ret = 0;


	}
	return (0);
}