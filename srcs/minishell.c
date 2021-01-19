#include "minishell.h"

void	free_2darray(char **array)
{
	int		i;

	i = 0;
	while (array && array[i])
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
		while (path && path[i])
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
		errors_handler("Command not found");
		exit(0);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
}

void 	switcher(char **command, char **envs, t_dict *dict)
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
	(*str)[j++] = '\0';
	free(tmp);
}

char	*cut_off_word(char **str, int start, int finish)
{
	char	*res;
	char	*tmp;
	char	*tmp2;
	int		cutted_len;
//	res = malloc(sizeof(char) * (finish - start + 2));

	cutted_len = (int)ft_strlen(*str) - (finish - start) + 1;
	res = ft_substr(*str, start, finish - start + 1);
//	res[finish - start] = '\0';
	tmp = *str;
	*str = malloc(sizeof(char) * cutted_len);
	ft_bzero(*str, cutted_len);
	ft_strlcat(*str, tmp, start);
	ft_strlcat(*str, tmp + finish + 1, cutted_len);
	free(tmp);
	tmp = ft_strtrim(res, " >");
//	trim(&res);
	tmp2 = *str;
	*str = ft_strtrim(tmp2, " >$");
	free(tmp2);
	free(res);
	return (tmp);
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
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777); // if -1 returns
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

//void	replace_char_by_str(char *dst, char c, char *str)
//{
//
//}

void	replace_vars(char **str, t_dict *dict)
{
	char	*tmp;
	int		i;
	int		len;
	char	*key;
	char	*value;

	i = 0;
//	trim(str);
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			tmp = ft_strdup(*str);
			key = cut_off_word(str, i + 1, i + 1 + index_before_spec_char(&((*str)[i + 1])));
			value = dict->get_value_by_key(dict, key);
			// some $var
			len = (int)(ft_strlen(tmp) - ft_strlen(key) + ft_strlen(value));
			*str = malloc(sizeof(char) * len);
			ft_bzero(*str, len);
			ft_strlcat(*str, tmp, i + 1);
			ft_strlcat(*str, value, len);
			ft_strlcat(*str, tmp + i + ft_strlen(key) + 1, len);
			free(tmp);
			free(key);
			i += ft_strlen(key);
			continue ;
		}
		i++;
	}
}

//void	replace_double_par(t_dict *dict, char **command, t_pair *parths, int i)
//{
//	char	*tmp;
//
//
//}
void	prths_back(char **command, t_pair *prths, int i)
{
	char	*tmp;

	tmp = *command;
	*command = malloc(sizeof(char) * (ft_strlen(*command) + ft_strlen(prths->key)));
	ft_bzero(*command, strlen(tmp));
	ft_strlcat(*command, tmp, i + 1);
	ft_strlcat(*command, prths->key, ft_strlen(tmp) + ft_strlen(prths->key));
	ft_strlcat(*command, tmp + i + 1, ft_strlen(tmp) + ft_strlen(prths->key));
}

void	del_front(t_pair **pair)
{
	t_pair	*tmp;
	tmp = *pair;
	*pair = (*pair)->next;
	free(tmp->key);
	free(tmp);
}

void	command_decomp(char **command, char **envs, t_dict *dict, t_pair **prths)
{
	char	**command_split;
	int		fd;
	int		i;
	int		saved_fd;
	int		j;

	i = 0;
	saved_fd = -1;
	saved_fd = dup(STDOUT_FILENO);
	while ((*command)[i])
	{
		if ((*command)[i] == '>')
		{
			fd = cut_off_redirect(command, i);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			continue;
		}

		i++;
	}
	i = 0;
	command_split = ft_split(*command, ' '); // need to free
	while (command_split[i])
	{
		j = 0;
		while (command_split[i][j])
		{
			if (command_split[i][j] == '"')
			{
				replace_vars(&(*prths)->key, dict);
				prths_back(&(command_split[i]), *prths, j);
				j += ft_strlen((*prths)->key);
				del_front(prths);
				continue ;
			}
			else if (command_split[i][j] == '\'')
			{
				prths_back(&(command_split[i]), *prths, j);
				j += ft_strlen((*prths)->key);
				del_front(prths);
				continue ;
			}
			j++;
		}
		i++;
	}
	switcher(command_split, envs, dict);
	if (saved_fd != -1)
	{
		dup2(saved_fd, STDOUT_FILENO);
		close(saved_fd);
	}
	free_2darray(command_split);
//	i = 0;
//	while (command_split[i])
//		free(command_split[i++]);
//	free(command_split);
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
			while ((*line)[j] && (*line)[j] != '\"')
				j++;
			if (!(*line)[j])
				return (NULL);
			ft_lstadd_back(&prths, ft_lstnew(ft_substr(*line, i + 1, j - i - 1), NULL));
			tmp = (*line);
			(*line) = cutstr((*line), i, j);
			free(tmp);
		}
		else if ((*line)[i] == '\'')
		{
			j++;
			while ((*line)[j] && (*line)[j] != '\'')
				j++;
			if (!(*line)[j])
				return (NULL);
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
	signal(SIGINT, &ft_ctrl_int);
	signal(SIGQUIT, &ft_ctrl_quit);
	while (1)
	{
		ft_printf("minishell-1.3$ ");
		get_next_line(0, &line);
		prths = NULL;
		if (ft_strrchr(line, '"') || ft_strrchr(line, '\''))
		{
			prths = parenthesis_handler(&line);
			if (!prths)
			{
				errors_handler("Syntax error");
				continue ;
			}
		}
		commands = ft_split(line, ';');
		i = 0;
		while (commands[i] != NULL)
		{
			replace_vars(&(commands[i]), dict);
			command_decomp(&commands[i++], envs, dict, &prths);
		}
		free_2darray(commands);
		free(line);
	}
}
