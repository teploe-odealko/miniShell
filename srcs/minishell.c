#include "minishell.h"
// Защитить маллоки форки риды


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

char 	**from_dict(t_dict *dict)
{
	t_pair	*pair;
	int		len;
	char	**env;
	int 	i;
	char 	*tmp;
	char	*tmpr;

	i = 0;
	pair = dict->pair;
	len = ft_lstsize(pair);
	if (len < 1)
		return (NULL);
	env = (char **)malloc(sizeof(char *) * (len + 1));
	if (!env)
		critical_errors_handler(strerror(errno));
	while (pair && i < len)
	{
		if (pair->key && pair->value && pair->value[0] == '\0')
			env[i] = ft_substr(pair->key, 0, ft_strlen(pair->key));
		else if (pair->key)
		{
			tmp = ft_strjoin(pair->key, "=");
			tmpr = ft_strjoin(tmp, pair->value);
			env[i] = tmpr;
			free(tmp);
		}
		i++;
		pair = pair->next;
	}
	env[i] = NULL;
	return (env);
}

void	check_exit_status(int status)
{
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_status = WTERMSIG(status) + 128;
}

void 	exec_other(char **command, char **envs, t_dict *dict)
{
	pid_t	pid;
	char	**path;
	char 	*tmp;
	char	*full_command;
	int		i;
	int		status;
	char	**env;

	(void)envs;
//	env = NULL;
	env = from_dict(dict);
	i = 0;
	if ((pid = fork()) == 0)
	{
		execve(command[0], command, env);
		path = ft_split(dict->get_value_by_key(dict, "PATH"), ':');
		while (path && path[i])
		{
			tmp = ft_strjoin(path[i], "/");
			full_command = ft_strjoin(tmp, command[0]);
			execve(full_command, command, env);
			free(full_command);
			free(tmp);
			i++;
		}
		free_2darray(path);
		errors_handler("Command not found");
		exit(127);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		check_exit_status(status);
		if (env)
			free_2darray(env);
	}
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

char	*cut_off_word(char **str, int start, int finish, char *trim_set)
{
	char	*res;
	char	*tmp;
	char	*tmp2;
	int		cutted_len;

	cutted_len = (int)ft_strlen(*str) - (finish - start) + 1;
	res = ft_substr(*str, start, finish - start + 1);
	tmp = *str;
	*str = malloc(sizeof(char) * cutted_len);
	ft_bzero(*str, cutted_len);
	ft_strlcat(*str, tmp, start);
	ft_strlcat(*str, tmp + finish + 1, cutted_len);
	free(tmp);
	tmp = ft_strtrim(res, trim_set);
//	trim(&res);
	tmp2 = *str;
	*str = ft_strtrim(tmp2, trim_set);
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

int 	cut_off_right_redirect(char **command, int i)
{
	int		j;
	int		fd;
	char	*filename;

	j = i + 1;
	if ((*command)[j] == '>')
	{
		j++;
		filename = cut_off_word(command, j, j + index_before_spec_char(&((*command)[j])), " >");
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777); // if -1 returns
	}
	else
	{
		filename = cut_off_word(command, j, j + index_before_spec_char(&((*command)[j])), " >");
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
//	if (fd < 0)
//		errors_handler(strerror(errno));
	free(filename);
	return (fd);
}

int 	cut_off_left_redirect(char **command, int i)
{
	int		j;
	int		fd;
	char	*filename;

	j = i + 1;
	filename = cut_off_word(command, j, j + index_before_spec_char(&((*command)[j])), " <");
	fd = open(filename, O_RDONLY);
	free(filename);
//	if (fd < 0)
//		errors_handler(strerror(errno));
	return (fd);
}

void	replace_vars(char **str, t_dict *dict)
{
	char	*str_dup;
	char	*tmp;
	int		i;
	int		len;
	char	*key;
	char	*value;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			if ((*str)[i + 1] == ' ' || (*str)[i + 1] == '\0')
			{
				i++;
				continue ;
			}
			str_dup = ft_strdup(*str);
			if ((*str)[i + 1] == '?')
			{
				value = ft_itoa(g_status);
				key = ft_strdup("?");
			}
			else
			{

				key = cut_off_word(str, i + 1, i + 1 + index_before_spec_char(&((*str)[i + 1])), " $");
				value = ft_strdup(dict->get_value_by_key(dict, key));
			}
			len = (int)(ft_strlen(str_dup) - ft_strlen(key) + ft_strlen(value));
			tmp = *str;
			*str = malloc(sizeof(char) * len);
			free(tmp);
			ft_bzero(*str, len);
			ft_strlcat(*str, str_dup, i + 1);
			ft_strlcat(*str, value, len);
			ft_strlcat(*str, str_dup + i + ft_strlen(key) + 1, len);
			i += ft_strlen(key);
			free(str_dup);
			free(key);
			free(value);
			continue ;
		}
		i++;
	}
}

void	prths_back(char **command, t_pair *prths, int i)
{
	char	*tmp;

	tmp = *command;
	*command = malloc(sizeof(char) * (ft_strlen(*command) + ft_strlen(prths->key)));
	ft_bzero(*command, strlen(tmp));
	ft_strlcat(*command, tmp, i + 1);
	ft_strlcat(*command, prths->key, ft_strlen(tmp) + ft_strlen(prths->key));
	ft_strlcat(*command, tmp + i + 1, ft_strlen(tmp) + ft_strlen(prths->key));
	free(tmp);
}

void	del_front(t_pair **pair)
{
	t_pair	*tmp;
	tmp = *pair;
	*pair = (*pair)->next;
	free(tmp->key);
	free(tmp);
}

void	run_cmd(char **command, t_pair **prths, t_dict *dict, char **envs)
{
	char	**command_split;
	int		i;
	int		j;
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
	free_2darray(command_split);
}

void	command_decomp(char **command, char **envs, t_dict *dict, t_pair **prths)
{
	int		fd;
	int		i;
	int		stdout_fd;
	int		stdin_fd;
	int		pipe_fd[2];

	i = 0;
	stdout_fd = dup(STDOUT_FILENO);
	stdin_fd = dup(STDIN_FILENO);
	while ((*command)[i])
	{
		if ((*command)[i] == '>')
		{
			fd = cut_off_right_redirect(command, i);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			continue;
		}
		if ((*command)[i] == '<')
		{
			fd = cut_off_left_redirect(command, i);
			dup2(fd, STDIN_FILENO);
			close(fd);
			continue;
		}

		// asd|asd
		else if ((*command)[i] == '|')
		{
			char	*left_com;
			char	*right_com;
			int		pid;

			left_com = ft_substr(*command, 0, i);
			right_com = ft_substr(*command, i + 1, ft_strlen(*command) - i - 1);
			pipe(pipe_fd);


			if ((pid = fork()) == 0)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				run_cmd(&left_com, prths, dict, envs);
				close(pipe_fd[1]);
				exit(0);
			}
			else if (pid > 0)
			{
				waitpid(pid, NULL, 0);
				char	*tmp;
				close(pipe_fd[1]);
				dup2(pipe_fd[0], STDIN_FILENO);
//				run_cmd(&left_com, prths, dict, envs);
				close(pipe_fd[0]);
//				exit(0);
				tmp = *command;
				*command = right_com;
				free(tmp);
				i = 0;
				continue ;
			}
			else
			{
				errors_handler("fork error"); // todo
			}
			fd = cut_off_left_redirect(command, i);
			dup2(fd, STDIN_FILENO);
			close(fd);

		}
		i++;
	}

	run_cmd(command, prths, dict, envs);
//	if (stdout_fd != -1)
//	{
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdout_fd);
	dup2(stdin_fd, STDIN_FILENO);
	close(stdin_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
//	}

}


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

void	main_loop(t_dict *dict, char **envs, char *res)
{
	//char	*line;
	t_pair 	*prths;
	char	**commands;
	int		i;


	//get_next_line(0, &line);
	prths = NULL;
	if (ft_strrchr(res, '"') || ft_strrchr(res, '\''))
	{
		prths = parenthesis_handler(&res);
		if (!prths)
		{
			errors_handler("Syntax error");
			return ;
		}
	}
	commands = ft_split(res, ';');
	i = 0;
	while (commands && commands[i] != NULL)
	{
		replace_vars(&(commands[i]), dict);
		command_decomp(&commands[i++], envs, dict, &prths);
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
				else
					ft_putstr_fd("  \b\b", 1);
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
		main_loop(dict, envs, res);
	}
}