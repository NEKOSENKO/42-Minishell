#include "../../minishell.h"

int norme_hack(char **argv, char *cur)
{
    char pwdold[1000];
    char *oldcur;
    if (chdir(argv[1]) == 0)
    {
        oldcur = getcwd(pwdold, 200);
        add_element("PWD", oldcur);
        add_element("OLDPWD", cur);
    }
    else
        senko_print("cd: ", "no such file or directory: ", argv[1], "\n");
    return (1);
}

void ft_cd(char **argv)
{
    char *cur;
    char pwdcur[1000];
    char *str;

    cur = getcwd(pwdcur, 200);
    str = get_var("HOME");
    if (!argv[1])
    {
        argv[0] = str;
        chdir(argv[0]);
    }
    else if (argv[0] && argv[1] && !argv[2])
        norme_hack(argv, cur);
    else if (argv[3])
        ft_putstr_fd("cd: too many arguments\n", 2);
    else if (argv[2] && !argv[3])
        senko_print("cd: ", "string not in pwd: ", argv[1], "\n");
}
