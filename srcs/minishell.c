#include "minishell.h"

void 	switcher(char **command, t_dict *dict)
{
	if (ft_streq(command[0], "echo"))
		ft_echo(command + 1);
	else if (ft_streq(command[0], "cd"))
		ft_cd(dict, command + 1);
	else if (ft_streq(command[0], "pwd"))
		ft_pwd(dict, command + 1);
	else if (ft_streq(command[0], "export"))
		ft_export(dict, command + 1);
	else if (ft_streq(command[0], "unset"))
		ft_unset(dict, command + 1);
	else if (ft_streq(command[0], "env"))
		ft_env(dict);
	else if (ft_streq(command[0], "exit"))
		ft_exit(command + 1);
	else
		exec_other(command, dict);
}

void	main_loop(t_dict *dict, char *res)
{
	char	**commands;
	int		i;

	dict->quotes = NULL;
	quotes_handler(&res, &dict->quotes);
	commands = ft_split(res, ';');
	i = 0;
	while (commands && commands[i] != NULL)
	{
		replace_vars(&(commands[i]), dict);
		command_decomp(&commands[i++], dict);
	}
	free_2darray(commands);
	free(res);
}

int		main(int argc, char **argv, char **envs) {
	char *res;
	char *tmp;
	char buf[2];
	t_dict *dict;

	g_status = 0;
	if (argc && argv) {}
	dict = set_env_to_dict(envs);
	signal(SIGINT, &ft_ctrl_int);
	signal(SIGQUIT, &ft_ctrl_quit);
	while (1)
	{
		ft_putstr_fd("minishell-1.3$ ", 1);
		buf[1] = 0;
		res = NULL;
		while (1)
		{
			tmp = res;
			if (read(0, buf, 1) == 0)
			{
				if (!tmp)
					break;
				continue;
			}
			if (!(res = ft_strjoin((res ? res : ""), (*buf == '\n' ? "" : buf))))
				critical_errors_handler(strerror(errno));
			if (tmp)
				free(tmp);
			if (*buf == '\n')
				break;
		}
		if (!res)
		{
			ft_putstr_fd("exit\n", 1);
			exit(1);
		}
		main_loop(dict, res);
	}
}
