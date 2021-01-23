/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_decomposition1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:21:22 by bashleig          #+#    #+#             */
/*   Updated: 2021/01/22 18:16:45 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(int *fd, int *pipe_fd)
{
	if (pipe_fd[0] != -1 && pipe_fd[1] != -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	close(fd[0]);
	close(fd[1]);
}

void	pipe_handler_parent(int pid, int *pipe_fd,
				char **command, char *right_com)
{
	char *tmp;

	waitpid(pid, NULL, 0);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	tmp = *command;
	*command = right_com;
	free(tmp);
}

void	pipe_handler_children(int *pipe_fd, t_dict *dict, char *left_com)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	run_cmd(&left_com, &dict->quotes, dict);
	close(pipe_fd[1]);
	exit(0);
}

t_pair	*free_quotes(t_pair **quotes)
{
	while (*quotes)
		del_front(quotes);
	return (NULL);
}
