#include "libft.h"

int	ft_streq(char *s1, char *s2)
{
	if (s1 && s2 && *s1 != '\0' && *s2 != '\0' && ft_strncmp(s1, s2, ft_max(ft_strlen(s1), ft_strlen(s2))) == 0)
		return (1);
	return (0);
}