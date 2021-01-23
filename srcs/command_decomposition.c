/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_decomposition.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:21:22 by bashleig          #+#    #+#             */
/*   Updated: 2021/01/22 17:40:56 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		right_redir_handler(char **command, int i)
{
	int		fd;

	fd = cut_off_right_redirect(command, i);
	if (fd < 0)
		return (1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int		left_redir_handler(char **command, int i)
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
	char	*left_com;
	char	*right_com;
	int		pid;

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
		pipe_handler_children(pipe_fd, dict, left_com);
	else if (pid > 0)
		pipe_handler_parent(pid, pipe_fd, command, right_com);
	else
		critical_errors_handler(strerror(errno));
	free(left_com);
	return (0);
}

void	dup_fd(int *fd, int *pipe_fd)
{
	fd[1] = dup(STDOUT_FILENO);
	fd[0] = dup(STDIN_FILENO);
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
}

void	command_decomp(char **command, t_dict *dict)
{
	int i;
	int fd[2];
	int pipe_fd[2];

	i = 0;
	dup_fd(fd, pipe_fd);
	while ((*command)[i] && i < (int)ft_strlen(*command))
	{
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
	close_pipe(fd, pipe_fd);
}
