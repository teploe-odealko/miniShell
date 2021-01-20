#include "minishell.h"

void	from_dict_helper(t_pair **pair, char **env, int *i)
{
	char 	*tmp;
	char	*tmpr;

	if ((*pair)->key && (*pair)->value && (*pair)->value[0] == '\0')
		env[*i] = ft_substr((*pair)->key, 0, ft_strlen((*pair)->key));
	else if ((*pair)->key)
	{
		tmp = ft_strjoin((*pair)->key, "=");
		tmpr = ft_strjoin(tmp, (*pair)->value);
		env[*i] = tmpr;
		free(tmp);
	}
	(*i)++;
	*pair = (*pair)->next;
}

char 	**from_dict(t_dict *dict)
{
	t_pair	*pair;
	int		len;
	char	**env;
	int 	i;

	i = 0;
	pair = dict->pair;
	len = ft_lstsize(pair);
	if (len < 1)
		return (NULL);
	env = (char **)malloc(sizeof(char *) * (len + 1));
	if (!env)
		critical_errors_handler(strerror(errno));
	while (pair && i < len)
		from_dict_helper(&pair, env, &i);
	env[i] = NULL;
	return (env);
}
