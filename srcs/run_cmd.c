#include "minishell.h"

void	run_cmd(char **command, t_pair **prths, t_dict *dict)
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
				insert_quotes_content(&(command_split[i]), *prths, j);
				j += ft_strlen((*prths)->key);
				del_front(prths);
				continue ;
			}
			else if (command_split[i][j] == '\'')
			{
				insert_quotes_content(&(command_split[i]), *prths, j);
				j += ft_strlen((*prths)->key);
				del_front(prths);
				continue ;
			}
			j++;
		}
		i++;
	}
	switcher(command_split, dict);
	free_2darray(command_split);
}