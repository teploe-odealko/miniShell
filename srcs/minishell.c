#include "minishell.h"

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

int		array2dlen(char **array2d)
{
	int	len;

	len = 0;
	while (array2d[len])
		len++;
	return (len);
}

//int		is_redirect_append(char *command)
//{
////	char *append_redirect;
//
//	while (!(command = ft_strnstr(command, ">>", ft_strlen(command))))
//	{
//		command += 2;
//		while (*command)
//			if (*command == '')
//	}
//	return (0);
//}

// danger! split

char	*insert_char_to_str(char *str, char *c, int i)
{
	char	*res;
	int		strlen;

	strlen = ft_strlen(str);
	res = malloc(sizeof(char) * (strlen + 2));
	ft_bzero(res, (strlen + 2));
	ft_strlcpy(res, str, i + 1);
	ft_strlcat(res, c, strlen + 2);
	ft_strlcat(res, str + i, strlen + 2);
	free(str);
	return (res);
}

char	*add_spaces(char *command)
{
	int		i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '<' || command[i] == '>' || command[i] == '|')
		{
			if (i > 0 && command[i - 1] != ' ')
			{
				command = insert_char_to_str(command, " ", i);
				i++;
			}
			if (command[i + 1] != ' ')
			{
				command = insert_char_to_str(command, " ", i + 1);
				i++;
			}
		}
		i++;
	}
	return (command);
}

void	command_decomp(char *command)
{
	char	**command_split;
	int		fd;
	command_split = ft_split(command, ' ');
	while (*command_split)
	{
		if (ft_streq(*command_split, ">"))
		{
			command_split++;
			if (ft_streq(*command_split, ">"))
			{
				command_split++;
				fd = open(*command_split, O_WRONLY | O_CREAT);
			}
			else
			{
				fd = open(*command_split, O_WRONLY | O_CREAT | O_TRUNC);
			}
		}
		command_split++;
	}
}
////	char	**redirect;
//	int		i;
//
//	i = (int)ft_strlen(command) - 1;
//	while (command[i])
//	{
//		if (ft_strncmp(&command[i], ">>", 2) == 0)
//		{
//
//		}
//	}
////	if ()
////	redirect = ft_split(command, '>');
//	if (array2dlen(redirect) >= 2)
//	{
//
//	}
//	ft_printf("%s\n", command);
//	while (*command)
//	{
//		if (*command == '>')
//		{
//
//		}
//		command++;
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
//	char	**command;

	while (1)
	{
		ft_printf("minishell$ ");
		get_next_line(0, &line);
//		commands = ft_split(line, ' ');

		prths = parenthesis_handler(&line);
		commands = ft_split(line, ';');
		while (*commands != NULL)
		{
			*commands = add_spaces(*commands);
			ft_printf("%s\n", *commands);
			command_decomp(*commands);
			commands++;
		}
//		ft_printf("%s\n", line);
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