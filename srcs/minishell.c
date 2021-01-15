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
	t_dict *dict;
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

	dict = set_env_to_dict(envs);
//	if (ft_streq(command[0], "echo"))
//		ft_echo(dict, command + 1, 1);
	if (ft_streq(command[0], "cd"))
		ft_cd(dict, command + 1, 1);
	else if (ft_streq(command[0], "pwd"))
		ft_pwd(dict, command + 1, 1);
//	else if (ft_streq(command[0], "export"))
//		ft_export(dict, command + 1, 1);
//	else if (ft_streq(command[0], "unset"))
//		ft_unset(dict, command + 1, 1);
//	else if (ft_streq(command[0], "env"))
//		ft_env(dict, command + 1, 1);
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



//void	command_decomp(char *line)
//{
//	while (*line)
//	{
//		if (*line == '\"')
//		{
//
//		}
//		line++;
//	}
//}
//
//char *replace_vars(char *s)
//{
//	char	**res;
//
//	while(s)
//	{
//		if (*s == '\'')
//		{
//
//		}
//		s++;
//	}
//}

char	*cutstr(char *line, int i, int j)
{
	char	*res;

	res = malloc(sizeof(char) * (ft_strlen(line) - (j - i) + 1));
	ft_strlcpy(res, line, i + 1);
	ft_strlcat(res, line + j, (ft_strlen(line) - (j - i) + 1));
	return (res);
}

t_pair	*parenthesis_handler(char **line)
{
	int		i;
	int		j;
	t_pair	*prths;
	char	*tmp;

	i = 0;
	prths = NULL;
	while ((*line)[i])
	{
		j = i;
		if ((*line)[i] == '\"')
		{
			j++;
			while ((*line)[j] != '\"')
				j++;
			ft_lstadd_back(&prths, ft_lstnew(ft_substr(*line, i + 1, j - i - 1), NULL));
			tmp = (*line);
			(*line) = cutstr((*line), i, j);
			free(tmp);
		}
		else if ((*line)[i] == '\'')
		{
			j++;
			while ((*line)[j] != '\'')
				j++;
			ft_lstadd_back(&prths, ft_lstnew(ft_substr(*line, i + 1, j - i - 1), NULL));
			tmp = (*line);
			(*line) = cutstr((*line), i, j);
			free(tmp);
		}
		i++;
	}
	return (prths);
}


int main(int argc, char **argv, char **envs)
{
	t_pair 	*prths;
	char	*line;
	char	**commands;

	while (1)
	{
		ft_printf("minishell$ ");
		get_next_line(0, &line);
//		commands = ft_split(line, ' ');

		prths = parenthesis_handler(&line);
		ft_printf("%s\n", line);
//		command_decomp(commands);
//		switcher(commands, envs);
		free(line);
	}

//	printf("%s - %s", "PWD", dict->get_value_by_key(dict, "PWD"));
//	printf("%s - %s\n", "PWD", dict->get_value_by_key(dict, "PWD"));
//	printf("%s - %s\n", "OLDPWD", dict->get_value_by_key(dict, "OLDPWD"));
	//ft_pwd(dict, NULL, 1);
//	ft_pwd(dict, NULL, 1);
//	ft_cd(dict, &flags, 1);
//	printf("%s - %s\n", "PWD", dict->get_value_by_key(dict, "PWD"));
//	printf("%s - %s\n", "OLDPWD", dict->get_value_by_key(dict, "OLDPWD"));

}