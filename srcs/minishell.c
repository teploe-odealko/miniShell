#include "minishell.h"

void	free_2darray(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void 	exec_other(char **command, char **envs, t_dict *dict)
{
	pid_t	pid;
	char	**path;
	char 	*tmp;
	char	*full_command;
	int		i;

	i = 0;
	if ((pid = fork()) == 0)
	{
		execve(command[0], command, envs);
		path = ft_split(dict->get_value_by_key(dict, "PATH"), ':');
		while (path[i])
		{
			tmp = ft_strjoin(path[i], "/");
//			printf("PATH - %s\n", path[i]);
			full_command = ft_strjoin(tmp, command[0]);
			execve(full_command, command, envs);
			free(full_command);
			free(tmp);
			i++;
		}
		free_2darray(path);
//		if (exec_res == -1)
		errors_handler("Command not found\n");
		exit(0);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
}

void 	switcher(char **command, char **envs, t_dict *dict)
{

//	t_dict *dict;
//
//	dict = set_env_to_dict(envs);
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
		exec_other(command, envs, dict);
}

int		array2dlen(char **array2d)
{
	int	len;

	len = 0;
	while (array2d[len])
		len++;
	return (len);
}

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

void	trim(char **str)
{
	int		counter;
	int		i;
	char	*tmp;
	int		j;

	counter = 0;
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == ' ')
			counter++;
		i++;
	}
	tmp = *str;
	*str = malloc(sizeof(char) * (strlen(*str) - counter + 1));
	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (tmp[i] != ' ')
			(*str)[j++] = tmp[i];
		i++;
	}
	free(tmp);
}

char	*cut_off_word(char **str, int start, int finish)
{
	char	*res;
	char	*tmp;
	int		cutted_len;
//	res = malloc(sizeof(char) * (finish - start + 2));
	cutted_len = (int)ft_strlen(*str) - (finish - start + 1);
	res = ft_substr(*str, start, finish - start + 1);
	tmp = *str;
	*str = malloc(sizeof(char) * cutted_len);
	ft_bzero(*str, ft_strlen(*str));
	ft_strlcat(*str, tmp, start);
	ft_strlcat(*str, tmp + finish + 1, cutted_len);
	free(tmp);
	trim(&res);
	return (res);
}

int		index_before_spec_char(char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<' || str[i] == '|' || str[i] == ' ')
			return (i - 1);
		i++;
	}
	return (i);
}

int 	cut_off_redirect(char **command, int i)
{
	int		j;
	int		fd;
	char	*filename;

	j = i + 1;
	if ((*command)[j] == '>')
	{
		j++;
		filename = cut_off_word(command, j, j + index_before_spec_char(&((*command)[j])));
		fd = open(filename, O_WRONLY | O_CREAT, 0777); // if -1 returns
		free(filename);
	}
	else
	{
		filename = cut_off_word(command, j, j + index_before_spec_char(&((*command)[j])));
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
//	if (fd < 0)
//		errors_handler(strerror(errno));
	return (fd);
}

void	command_decomp(char *command, char **envs, t_dict *dict)
{
	char	**command_split;
	int		fd;
	int		i;
	int		saved_fd;

	i = 0;
	saved_fd = -1;
	saved_fd = dup(STDOUT_FILENO);
	while (command[i])
	{
		if (command[i] == '>')
		{
			fd = cut_off_redirect(&command, i);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		i++;
	}
	command_split = ft_split(command, ' '); // need to free
	switcher(command_split, envs, dict);
	if (saved_fd != -1)
	{
		dup2(saved_fd, STDOUT_FILENO);
		close(saved_fd);
	}
}

//char *replace_vars(char *s)
//{

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
	t_dict	*dict;
	int		i;

	if (argc && argv) {}
	dict = set_env_to_dict(envs);
	while (1)
	{
		ft_printf("minishell-1.1$ ");
		get_next_line(0, &line);
//		commands = ft_split(line, ' ');

		prths = parenthesis_handler(&line);
		commands = ft_split(line, ';');
		i = 0;
		while (commands[i] != NULL)
			command_decomp(commands[i++], envs, dict);
		i = 0;
		while (commands[i])
		{
			free(commands[i]);
			i++;
		}
		free(commands);
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