#include "minishell.h"
#include "ft_printf.h"
#include <unistd.h>
#include <stdio.h>
#include "string.h"
#include "errno.h"

void 	switcher(char **command, char **envs)
{
	pid_t	pid;
	int		child_exit_stat;

	if (ft_streq(command[0], "echo"))
		ft_echo();

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
	t_dict *dict;
	char	*line;
	char	**command;


	dict = set_env_to_dict(envs);

	while (1)
	{
		ft_printf("minishell$ ");
		get_next_line(0, &line);
		command = ft_split(line, ' ');
		switcher(command, envs);
		free(line);
	}

//	printf("%s - %s", "PWD", dict->get_value_by_key(dict, "PWD"));

}