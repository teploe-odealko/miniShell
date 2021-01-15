#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

//void 	switcher(char **command)
//{
//	if (ft_streq(command[0], "echo"))
//		ft_echo();
//}

int main(int argc, char **argv, char **envs)
{
	t_dict *dict;
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

	dict = set_env_to_dict(envs);
	printf("%s - %s\n", "PWD", dict->get_value_by_key(dict, "PWD"));
	printf("%s - %s\n", "SHELL", dict->get_value_by_key(dict, "SHELL"));

}