/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 18:19:06 by bashleig          #+#    #+#             */
/*   Updated: 2021/01/22 18:19:06 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	switcher(char **command, t_dict *dict)
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
		ft_env(dict, command + 1);
	else if (ft_streq(command[0], "exit"))
		ft_exit(command + 1);
	else if (*command != NULL)
		exec_other(command, dict);
}

int		smcln1(char *res)
{
	while (*res == ' ')
		res++;
	if (*res == ';')
		return (1);
	return (0);
}

void	main_loop(t_dict *dict, char *res)
{
	char	**commands;
	int		i;

	dict->quotes = NULL;
	if (!quotes_handler(&res, &dict->quotes))
	{
		free(res);
		return ;
	}
	commands = ft_split(res, ';');
	if (smcln(res) || (!commands[0] && ft_strchr(res, ';')) || smcln1(res))
	{
		free_2darray(commands);
		errors_handler("Syntax error");
		free(res);
		return ;
	}
	i = 0;
	while (commands && commands[i] != NULL)
	{
		replace_vars(&(commands[i]), dict);
		command_decomp(&commands[i++], dict);
	}
	free_2darray(commands);
	free(res);
}

char	*get_one_line(void)
{
	char *line;
	char *tmp;
	char buf[2];

	buf[1] = 0;
	line = NULL;
	while (1)
	{
		tmp = line;
		if (read(0, buf, 1) == 0)
		{
			if (!tmp)
				break ;
			else
				ft_putstr_fd("  \b\b", 1);
			continue ;
		}
		if (!(line = ft_strjoin((line ? line : ""), (*buf == '\n' ? "" : buf))))
			critical_errors_handler(strerror(errno));
		if (tmp)
			free(tmp);
		if (*buf == '\n')
			break ;
	}
	return (line);
}

int		main(int argc, char **argv, char **envs)
{
	t_dict	*dict;
	char	*line;

	g_status = 0;
	if (argc && argv)
		NULL;
	dict = set_env_to_dict(envs);
	signal(SIGINT, &ft_ctrl_int);
	signal(SIGQUIT, &ft_ctrl_quit);
	while (1)
	{
		ft_putstr_fd("minishell-1.3$ ", 1);
		line = get_one_line();
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			exit(1);
		}
		main_loop(dict, line);
	}
}
