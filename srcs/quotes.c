#include "minishell.h"

void	insert_quotes_content(char **command, t_pair *prths, int i)
{
	char	*tmp;

	tmp = *command;
	*command = malloc(sizeof(char) * (ft_strlen(*command) + ft_strlen(prths->key)));
	if (!*command)
		critical_errors_handler(strerror(errno));
	ft_bzero(*command, strlen(tmp));
	ft_strlcat(*command, tmp, i + 1);
	ft_strlcat(*command, prths->key, ft_strlen(tmp) + ft_strlen(prths->key));
	ft_strlcat(*command, tmp + i + 1, ft_strlen(tmp) + ft_strlen(prths->key));
	free(tmp);
}

int		single_quotes(int *j, int i, char **line, t_pair **quotes)
{
	char	*tmp;
	*j += 1;
	while ((*line)[*j] && (*line)[*j] != '\'')
		*j += 1;
	if (!(*line)[*j])
		return (0);
	ft_lstadd_back(quotes, ft_lstnew(ft_substr(*line, i + 1, *j - i - 1), NULL));
	tmp = (*line);
	(*line) = cut_center((*line), i, *j);
	free(tmp);
	return (1);
}

int		double_quotes(int *j, int i, char **line, t_pair **quotes)
{
	char	*tmp;
	*j += 1;
	while ((*line)[*j] && (*line)[*j] != '\"')
		*j += 1;
	if (!(*line)[*j])
		return (0);
	ft_lstadd_back(quotes, ft_lstnew(ft_substr(*line, i + 1, *j - i - 1), NULL));
	tmp = (*line);
	(*line) = cut_center((*line), i, *j);
	free(tmp);
	return (1);
}

t_pair	*extract_quotes(char **line)
{
	int		i;
	int		j;
	t_pair	*quotes;

	i = 0;
	quotes = NULL;
	while ((*line)[i])
	{
		j = i;
		if ((*line)[i] == '\"')
		{
			if (!double_quotes(&j, i, line, &quotes))
				return (NULL);
		}
		else if ((*line)[i] == '\'')
		{
			if (!single_quotes(&j, i, line, &quotes))
				return (NULL);
		}
		i++;
	}
	return (quotes);
}

void	quotes_handler(char *line, t_pair *prths)
{
	if (ft_strrchr(line, '"') || ft_strrchr(line, '\''))
	{
		prths = extract_quotes(&line);
		if (!prths)
		{
			errors_handler("Syntax error");
			return ;
		}
	}
}
