#include "minishell.h"

char	*cut_center(char *line, int i, int j)
{
	char	*res;

	res = malloc(sizeof(char) * (ft_strlen(line) - (j - i) + 1));
	if (!res)
		critical_errors_handler(strerror(errno));
	ft_strlcpy(res, line, i + 1);
	ft_strlcat(res, line + j, (ft_strlen(line) - (j - i) + 1));
	return (res);
}

