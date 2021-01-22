#include "minishell.h"

int 	right_redir_handler(char **command, int i)
{
	int		fd;
	fd = cut_off_right_redirect(command, i);
	if (fd < 0)
		return (1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int 	left_redir_handler(char **command, int i)
{
	int		fd;

	fd = cut_off_left_redirect(command, i);
	if (fd < 0)
		return (1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int		pipe_handler(int *pipe_fd, char **command, int i, t_dict *dict)
{
	char *left_com;
	char *right_com;
	int pid;

	left_com = ft_substr(*command, 0, i);
	right_com = ft_substr(*command, i + 1, ft_strlen(*command) - i - 1);
	if (!*left_com || !*right_com)
	{
		free(left_com);
		free(right_com);
		errors_handler("Syntax error");
		return (-1);
	}
	pipe(pipe_fd);
	if ((pid = fork()) == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		run_cmd(&left_com, &dict->quotes, dict);
		close(pipe_fd[1]);
		exit(0);
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		char *tmp;
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		tmp = *command;
		*command = right_com;
		free(tmp);
		free(left_com);
	}
	else
		critical_errors_handler(strerror(errno));
	return (0);
}

void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void command_decomp(char **command, t_dict *dict)
{
	int i;
	int fd[2];
	int pipe_fd[2];

	i = 0;
	fd[1] = dup(STDOUT_FILENO);
	fd[0] = dup(STDIN_FILENO);
	while ((*command)[i] && i < (int)ft_strlen(*command)) {
		if ((*command)[i] == '>' && right_redir_handler(command, i))
			continue ;
		else if ((*command)[i] == '<' && left_redir_handler(command, i))
			continue ;
		else if ((*command)[i] == '|')
		{
			if (pipe_handler(pipe_fd, command, i, dict) < 0)
				return ;
			i = 0;
			continue;
		}
		i++;
	}
	run_cmd(command, &dict->quotes, dict);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close_pipe(fd);
	close_pipe(pipe_fd);
}
