#include "minishell.h"

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
			if (!*str)
				critical_errors_handler(strerror(errno));
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