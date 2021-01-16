#include "minishell.h"
#include "string.h"
#include "errno.h"

static	void	parse_and_add(t_dict *dict, char *env)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (env[i] != '=')
		i++;
	if (!(key = ft_substr(env, 0, i)) ||
		!(value = ft_substr(env, i+1, ft_strlen(env) - i - 1)))
		errors_handler(strerror(errno));
	dict->add_new_key(dict, key, value);
}

t_dict	*set_env_to_dict(char **envs)
{
	t_dict	*dict;

	dict = new_dict();
	while(envs && *envs)
	{
		parse_and_add(dict, *envs);
		(envs)++;
	}
	return (dict);
}