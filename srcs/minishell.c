#include "minishell.h"
#include "ft_printf.h"
#include <unistd.h>
#include <stdio.h>
#include "string.h"
#include "errno.h"

void 	switcher(char **command, t_dict *dict, char **envs)
{
	pid_t	pid;
	int		child_exit_stat;
	char	*flags = {"CMakeFiles//"};
//	char	*line;
//	char	**command;
//	int		pid;

//	while (1)
//	{
//		get_next_line(0, &line);
//		command = ft_split(line, ' ');
//		if (execve(command[0], command, envp) == -1)
//			errors_handler("Could not execve");
//		free(line);
//	}

//	if (ft_streq(command[0], "echo"))
//		ft_echo(dict, command + 1, 1);
	if (ft_streq(command[0], "cd"))
		ft_cd(dict, command + 1, 1);
	else if (ft_streq(command[0], "pwd"))
		ft_pwd(dict, command + 1, 1);
	else if (ft_streq(command[0], "export"))
		ft_export(dict, command + 1, 1);
	else if (ft_streq(command[0], "unset"))
		ft_unset(dict, command + 1, 1);
	else if (ft_streq(command[0], "env"))
		ft_env(dict, command + 1, 1);
//	else if (ft_streq(command[0], "exit"))
//		ft_exit(dict, command + 1, 1);
	else
		if ((pid = fork()) == 0)
		{
			if (execve(command[0], command, envs) == -1)
				errors_handler(strerror(errno));
			exit(0);
		}
		else if (pid > 0)
			waitpid(pid, &child_exit_stat, 0);
}


int main(int argc, char **argv, char **envs)
{
	char	*line;
	char	**command;
	t_dict	*dict;
	int		i;

	dict = set_env_to_dict(envs);
	while (1)
	{
		ft_printf("minishell$ ");
		get_next_line(0, &line);
		command = ft_split(line, ' ');
		switcher(command, dict, envs);
		i = 0;
		while (command[i])
		{
			free(command[i]);
			i++;
		}
		free(command);
		free(line);
	}
}