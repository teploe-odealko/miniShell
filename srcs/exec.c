/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 18:12:52 by bashleig          #+#    #+#             */
/*   Updated: 2021/01/22 18:13:01 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execve_handler(char **command, t_dict *dict, char **env)
{
	char	*tmp;
	char	**path;
	char	*full_command;
	int		i;

	i = 0;
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
	exit(0);
}

void		exec_other(char **command, t_dict *dict)
{
	pid_t	pid;
	int		status;
	char	**env;

	env = from_dict(dict);
	if ((pid = fork()) == 0)
	{
		if (*command)
			execve_handler(command, dict, env);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		check_exit_status(status);
		if (env)
			free_2darray(env);
	}
	else
		critical_errors_handler(strerror(errno));
}
